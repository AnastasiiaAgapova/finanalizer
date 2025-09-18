#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "databasemodel.h"

namespace Widgets
{
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

private:
    DatabaseModel *_model;
    Transactions::Database *_database;
    PieChartBuilder *_builder;
    DateRangeEdit *_dateRangeEdit;
};
}

#endif // MAINWINDOW_H
