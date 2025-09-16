#include "mainwindow.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QFileDialog>

namespace Widgets
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , _model(new DatabaseModel(this))
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QTableView *transactionsView = new QTableView(centralWidget);
    mainLayout->addWidget(transactionsView);
    // openDatabase();
    transactionsView->setModel(_model);

    QPushButton *openDatabaseButton = new QPushButton("Open", centralWidget);
    mainLayout->addWidget(openDatabaseButton);
    connect(openDatabaseButton, SIGNAL(pressed()), this, SLOT(openDatabase()));

}

void MainWindow::openDatabase()
{
    Transactions::Database *db = new Transactions::Database(this);
    db->setFileName("C:\\workspace\\finanalizer\\examples\\database.json");
    db->load();
    _model->setDatabase(db);
}
}
