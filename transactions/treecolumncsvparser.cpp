#include "treecolumncsvparser.h"

#include <QFile>
#include <QTextStream>

namespace Transactions
{
TreeColumnCsvParser::TreeColumnCsvParser()
        : _categoryDetector(nullptr)
{

}

QList<Transaction> TreeColumnCsvParser::load(const QString &connectionString) const
{
    QList<Transaction> res;
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

            Transaction transaction;
            bool ok;
            transaction.setAmount(stringList[2].toDouble(&ok) * 100);
            if (!ok)
                continue;
            transaction.setDateTime(QDateTime::fromString(stringList[0], "dd/MM/yyyy"));
            transaction.setDescription(stringList[1]);

            if (_categoryDetector)
                _categoryDetector->detect(transaction);

            res << transaction;
        }
    }
    return res;
}

void TreeColumnCsvParser::setCategoryDetector(CategoryDetector *newCategoryDetector)
{
    _categoryDetector = newCategoryDetector;
}
}
