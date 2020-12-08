#ifndef NN_H
#define NN_H

#include "PathFinder.h"


std::vector<bool> visited;
std::unordered_map<int, Product*> indexToProduct;
std::vector<int> finalPath;
std::unordered_map<double,bool> canVisit;

double distanceBetweenProductsEuclidean(Product& product1, Product& product2);

QVector<QPointF> NNAlgorithm(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation
            );


#endif
