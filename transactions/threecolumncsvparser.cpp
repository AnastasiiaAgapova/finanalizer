#include "threecolumncsvparser.h"

#include <QFile>
#include <QTextStream>

#include "transaction.h"

namespace Transactions
{
ThreeColumnCsvParser::ThreeColumnCsvParser()
        : _categoryDetector(nullptr)
{

}

QVector<std::shared_ptr<Transaction>> ThreeColumnCsvParser::load(const QString &connectionString) const
{
    QVector<std::shared_ptr<Transaction>> res;
    QFile file(connectionString);
    if (file.open(QFile::ReadOnly))
    {
        QTextStream textStream(&file);
        QString line = textStream.readLine();
        while(!line.isNull())
        {
            QStringList stringList = line.split(',');
            if (stringList.size() != 3)
                return res;

            line = textStream.readLine();

            auto transaction = std::make_shared<Transaction>();
            bool ok;
            double amount = stringList[2].toDouble(&ok);
            transaction->setType(amount < 0 ? Transaction::OUTCOME : Transaction::INCOME);
            transaction->setAmount(amount * 100);
            if (!ok)
                continue;
            transaction->setDateTime(QDateTime::fromString(stringList[0], "dd/MM/yyyy"));
            transaction->setDescription(stringList[1]);

            if (_categoryDetector)
                _categoryDetector->detect(transaction);

            res << transaction;
        }
    }
    return res;
}

void ThreeColumnCsvParser::setCategoryDetector(CategoryDetector *newCategoryDetector)
{
    _categoryDetector = newCategoryDetector;
}
}
