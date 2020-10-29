/*********************************************************************
 * @file   PathFinder.h
 * @brief  This header includes the PathFinder. The PathFinder class 
 *			contains members: distance and visted which are unorderdered
            maps. The path is a deque of productIDs showing the path the 
            user has to take
 *			
 * @author Abinav
 * @date   October 2020
 *********************************************************************/

#include <limits.h>
#include <math.h>
#include <iomanip>
#include <sstream>

#include <QVector>
#include <QPointF>

#include "AdjacencyMatrix.h"

class PathFinder {
    private:
    double pathLength;
    std::deque<Product> path;
    std::unordered_map<std::string,float> distance;
    std::unordered_map<std::string,bool>  visited;
    const float TILE_SIZE = 30;
    const float SCALE = 5;

    public:

    std::deque<Product> calculatePath(
        std::unordered_map<Product*, std::deque<Product>> graph, 
        std::deque<Product> productList,
        Product startLocation,
        Product endLocation
        );

    float calculatePathAlternate(
        std::unordered_map<Product*, std::deque<Product>> graph, 
        std::deque<Product> productList,
        Product startLocation,
        Product endLocation
        );

    std::deque<Product> singleProductPath(
        Product& product, 
        Product startLocation,
        Product endLocation
        );

    double distanceBetweenProducts(Product& product1, Product& product2);
    std::deque<Product> getPath(void);
    QVector <QPointF> displayPath(void);
    QVector <std::string> pathAnnotation(std::deque<Product>& path);

};
