#include "daterangeedit.h"

#include <QBoxLayout>
#include <QDateEdit>
#include <QLabel>

namespace Widgets
{
DateRangeEdit::DateRangeEdit(QWidget *parent)
    : QWidget{parent}
    , _startDateEdit(new QDateEdit(this))
    , _endDateEdit(new QDateEdit(this))
{
    _startDateEdit->setDate(QDate(2000, 1, 1));
    _endDateEdit->setDate(QDate(2999, 12, 31));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    setLayout(mainLayout);
    mainLayout->addWidget(new QLabel("From", this));
    mainLayout->addWidget(_startDateEdit);
    mainLayout->addWidget(new QLabel("to", this));
    mainLayout->addWidget(_endDateEdit);

    connect(_startDateEdit, &QDateEdit::dateChanged, this, &DateRangeEdit::dateRangeChanged);
    connect(_endDateEdit, &QDateEdit::dateChanged, this, &DateRangeEdit::dateRangeChanged);
}

void DateRangeEdit::setMaxDateRange(const QDate &minDate, const QDate &maxDate)
{
    _startDateEdit->setDateRange(minDate, maxDate);
    _endDateEdit->setDateRange(minDate, maxDate);
}

QDate DateRangeEdit::startDate() const
{
    return _startDateEdit->date();
}

QDate DateRangeEdit::endDate() const
{
    return _endDateEdit->date();
}
}
