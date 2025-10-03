#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Calculation
{
class AiModel;
}
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
    void analyzeUsingMAD();
    void createAiModel();
    void analyzeUsingAi();

private:
    DatabaseModel *_model;
    DatabesaSortFilterProxyModel *_proxyModel;
    std::shared_ptr<Calculation::AiModel> _aiModel;

    Transactions::Database *_database;
    PieChartBuilder *_incomeBuilder;
    PieChartBuilder *_outcomeBuilder;
    DateRangeEdit *_dateRangeEdit;
};

}

#endif // MAINWINDOW_H
