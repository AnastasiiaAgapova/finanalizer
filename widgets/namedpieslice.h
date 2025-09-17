#ifndef NAMEDPIESLICE_H
#define NAMEDPIESLICE_H

#include <QtCharts/QPieSlice>

namespace Widgets
{
class NamedPieSlice : public QPieSlice
{
public:
    explicit NamedPieSlice(int value, const QString &name);

public slots:
    void updateLabel();
    void showHighlight(bool show);

private:
    QString _name;
};
}
#endif // NAMEDPIESLICE_H
