import argparse
import pandas as pd
import torch
from torch import nn
from torch.utils.data import DataLoader, Dataset

# --- аргументы командной строки ---
parser = argparse.ArgumentParser(description="Train anomaly detection model")
parser.add_argument("--data", type=str, required=True, help="Path to CSV file with transactions")
parser.add_argument("--output", type=str, required=True, help="Path to model")

args = parser.parse_args()

print(args.data)
print(args.output)

# --- читаем CSV ---
df = pd.read_csv(args.data)

print(df.columns)

X = df[["CategoryHash", "Amount"]].values.astype("float32")
y = df["IsAnomaly"].values.astype("float32")

# --- Dataset ---
class TransactionDataset(Dataset):
    def __init__(self, X, y):
        self.X = torch.tensor(X, dtype=torch.float32)
        self.y = torch.tensor(y, dtype=torch.float32)

    def __len__(self):
        return len(self.X)

    def __getitem__(self, idx):
        return self.X[idx], self.y[idx]

dataset = TransactionDataset(X, y)
dataloader = DataLoader(dataset, batch_size=16, shuffle=True)

# --- Модель ---
class AnomalyModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(2, 32),
            nn.ReLU(),
            nn.Linear(32, 16),
            nn.ReLU(),
            nn.Linear(16, 1),
            nn.Sigmoid()
        )


    def forward(self, x):
        return self.net(x)

model = AnomalyModel()
n_normal = (y == 0).sum()
n_anomaly = (y == 1).sum()
weight = torch.tensor([n_normal / n_anomaly], dtype=torch.float32)
criterion = nn.BCELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# --- Обучение ---
for epoch in range(200):
    for batch_X, batch_y in dataloader:
        preds = model(batch_X).squeeze()
        loss = criterion(preds, batch_y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
    print(f"Epoch {epoch+1}, Loss: {loss.item():.4f}")

# --- Сохранение в ONNX ---
dummy_input = torch.tensor([[0.0, 0.0]])
torch.onnx.export(
    model,
    dummy_input,
    args.output,
    input_names=["input"],
    output_names=["output"],
    dynamic_axes={"input": {0: "batch_size"}, "output": {0: "batch_size"}},
)

print("✅ Model trained and saved to " + args.output)
