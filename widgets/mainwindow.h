#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Transactions
{
class Database;
}

namespace Widgets
{
class DatabaseModel;
class DatabesaSortFilterProxyModel;
class PieChartBuilder;
class DateRangeEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

protected:
    void closeEvent(QCloseEvent *event) override;

protected slots:
    void openDatabase();
    void addData();
    void onDateRangeChanged();
    void onDatabaseChaned();
    void analyze();

private:
    DatabaseModel *_model;
    DatabesaSortFilterProxyModel *_proxyModel;

    Transactions::Database *_database;
    PieChartBuilder *_incomeBuilder;
    PieChartBuilder *_outcomeBuilder;
    DateRangeEdit *_dateRangeEdit;
};
}

#endif // MAINWINDOW_H
