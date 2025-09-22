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
    ~ThreeColumnCsvParser() override {}

    QVector<std::shared_ptr<Transaction>> load(const QString &connectionString) const override;

    void setCategoryDetector(CategoryDetector *newCategoryDetector);

private:
    CategoryDetector* _categoryDetector;
};
}

#endif // THREECOLUMNCSVPARSER_H
