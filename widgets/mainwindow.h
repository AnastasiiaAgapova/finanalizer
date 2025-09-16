#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "databasemodel.h"

namespace Widgets
{
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void openDatabase();
signals:

private:
    DatabaseModel *_model;
};
}

#endif // MAINWINDOW_H
