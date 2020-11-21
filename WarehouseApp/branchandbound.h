#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <PathFinder.h>

class BranchAndBound
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

    QVector<QPointF> branchAndBound(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation
            );

    int firstMin(std::vector<std::vector<int> >& matrix, int i);
    int secondMin(std::vector<std::vector<int> >& matrix, int i);
    void copyToFinal(std::vector<int>& currPath);
    void TSPRec(std::vector<std::vector<int> >& matrix, int currBound, int currWeight,
                int level, std::vector<int>&, std::deque<Product>&);

};

#endif // BRANCHANDBOUND_H
