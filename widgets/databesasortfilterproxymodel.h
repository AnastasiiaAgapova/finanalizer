#ifndef DATABESASORTFILTERPROXYMODEL_H
#define DATABESASORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

#include "transactions/filter.h"

namespace Widgets
{
class DatabesaSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    explicit DatabesaSortFilterProxyModel(QObject *parent = nullptr);

    void setFilter(const std::shared_ptr<Transactions::Filter> &newFilter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    std::shared_ptr<Transactions::Filter> _filter;
};
}

#endif // DATABESASORTFILTERPROXYMODEL_H
