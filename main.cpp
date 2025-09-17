#include <QApplication>

// #include "transactions/treecolumncsvparser.h"
// #include "transactions/database.h"
// #include "transactions/simplecategorydetector.h"
#include "widgets/mainwindow.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // Transactions::TreeColumnCsvParser parser;
        // parser.setCategoryDetector(new Transactions::SimpleCategoryDetector());
        // QList<Transactions::Transaction *> transactions = parser.load("C:\\workspace\\finanalizer\\examples\\expenses_2024.csv");

        // Transactions::Database db;
        // db.setFileName("C:\\workspace\\finanalizer\\examples\\database.json");
        // foreach(auto transaction, transactions)
        //     db.addTransaction(transaction);
        // qDebug() << db.save();

        // Transactions::Database db;
        // db.setFileName("C:\\workspace\\finanalizer\\examples\\database.json");
        // db.load();
        // for (auto transaction : db.transactions())
        //     qDebug() << transaction.id() << " "
        //              << transaction.dateTime() << " "
        //              << transaction.amount() << " "
        //              << transaction.category() << " "
        //              << transaction.description();
    }
    QApplication a(argc, argv);

    Widgets::MainWindow *mainWindow = new Widgets::MainWindow();
    mainWindow->show();

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
