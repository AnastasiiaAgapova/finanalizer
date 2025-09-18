#include "namedpieslice.h"

namespace Widgets
{

NamedPieSlice::NamedPieSlice(int value, const QString &name)
    : _name(name)
{
    setValue(value * 0.01);
    updateLabel();
    QObject::connect(this, &NamedPieSlice::percentageChanged, this, &NamedPieSlice::updateLabel);
    QObject::connect(this, &NamedPieSlice::hovered, this, &NamedPieSlice::showHighlight);
}

void NamedPieSlice::updateLabel()
{
    setLabel(QStringLiteral("%1 £%2, %3%").arg(_name,
                                               QString::number(value()),
                                               QString::number(percentage() * 100, 'f', 1)));
}

void NamedPieSlice::showHighlight(bool show)
{
    setLabelVisible(show);
    setExploded(show);
}

}
