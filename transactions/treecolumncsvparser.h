#ifndef TREECOLUMNCSVPARSER_H
#define TREECOLUMNCSVPARSER_H

#include "categorydetector.h"
#include "connector.h"

namespace Transactions
{
class TreeColumnCsvParser : public Connector
{
public:
    TreeColumnCsvParser();
    ~TreeColumnCsvParser(){}

    QList<Transaction *> load(const QString &connectionString) const;

    void setCategoryDetector(CategoryDetector *newCategoryDetector);

private:
    CategoryDetector* _categoryDetector;
};
}

#endif // TREECOLUMNCSVPARSER_H
