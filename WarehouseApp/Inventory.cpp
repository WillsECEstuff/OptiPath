#include "Inventory.h"
#include <iostream>

Inventory::Inventory(QVector<QPointF> aL, QVector<QPointF> pL) {
    allListLoc = aL;
    prodListLoc = pL;
    std::cout << "successfully created inventory" << std::endl;
}

QVector<QPointF> Inventory::getProdLocList() {
    std::cout << "successfully read products" << std::endl;
    return prodListLoc;
}

QVector<QPointF> Inventory::getAllLocList() {
    std::cout << "successfully read all" << std::endl;
    return allListLoc;
}
