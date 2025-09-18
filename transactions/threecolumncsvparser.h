#ifndef THREECOLUMNCSVPARSER_H
#define THREECOLUMNCSVPARSER_H

#include "categorydetector.h"
#include "connector.h"

namespace Transactions
{
class ThreeColumnCsvParser : public Connector
{
public:
    ThreeColumnCsvParser();
    ~ThreeColumnCsvParser(){}

    QList<Transaction> load(const QString &connectionString) const;

    void setCategoryDetector(CategoryDetector *newCategoryDetector);

private:
    CategoryDetector* _categoryDetector;
};
}

#endif // THREECOLUMNCSVPARSER_H
