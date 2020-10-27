#include <limits.h>
#include <math.h>

#include "AdjacencyMatrix.h"

class PathFinder {
    private:
    std::deque<std::string> path;
    std::unordered_map<std::string,float> distance;
    std::unordered_map<std::string,bool>  visited;

    public:
    std::deque<std::string> calculatePath(
        std::unordered_map<Product*, std::deque<Product>>& graph, 
        std::tuple<float,float> startLocation,
        std::tuple<float,float> endLocation
        );

    std::deque<std::string> singleProductPath(
        Product& product, 
        std::tuple<float,float> startLocation,
        std::tuple<float,float> endLocation
        );

    std::string minDistance();
    float distanceBetweenProducts(Product& product1, Product& product2);
};