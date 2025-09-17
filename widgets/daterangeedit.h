#ifndef DATERANGEEDIT_H
#define DATERANGEEDIT_H

#include <QWidget>
#include <QDate>

class QDateEdit;
namespace Widgets
{
class DateRangeEdit : public QWidget
{
    Q_OBJECT
public:
    explicit DateRangeEdit(QWidget *parent = nullptr);

    void setMaxDateRange(const QDate &minDate, const QDate &maxDate);

    QDate startDate() const;
    QDate endDate() const;

signals:
    void dateRangeChanged();

private:
    QDate _minDate;
    QDate _maxDate;

    QDateEdit *_startDateEdit;
    QDateEdit *_endDateEdit;
};
}

#endif // DATERANGEEDIT_H
