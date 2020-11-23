#ifndef NN_H
#define NN_H

#include "PathFinder.h"

class NN
{

private:
    int minPathLength = INT_MAX;
    const float TILE_SIZE = 30;
    const float SCALE = 5;

public:
    std::vector<bool> visited;
    std::unordered_map<int, Product*> indexToProduct;
    std::vector<int> finalPath;

    double distanceBetweenProductsEuclidean(Product& product1, Product& product2);

    QVector<QPointF> NNAlgorithm(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation
            );

};

#endif
