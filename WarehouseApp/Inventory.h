#ifndef INVENTORY_H
#define INVENTORY_H

#include <QPointF>
#include <QVector>

/******
 *
 * Unused at the moment
 * ****/

class Inventory
{
private:
    QVector <QPointF> allListLoc;
    QVector <QPointF> prodListLoc;

public:
    Inventory(QVector<QPointF> aL, QVector<QPointF> pL);

    QVector<QPointF> getAllLocList();
    QVector<QPointF> getProdLocList();
};

#endif // INVENTORY_H
