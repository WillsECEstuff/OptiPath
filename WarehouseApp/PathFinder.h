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
#pragma once

#include <limits.h>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <QVector>
#include <QPointF>

#include "AdjacencyMatrix.h"
#include "WarehouseMap.h"

class PathFinder {
    private:
    double pathLength;
    std::tuple<float,float> currentPosition;
    std::vector<int> aislesToBeVisited;
    std::tuple<float,float> points;
    std::deque<Product> path;
    const std::string NOT_PRODUCT = "-1";
    const float TILE_SIZE = 30;
    const float SCALE = 5;

    public:

    int findMaxEnd(int, int);
    int findMinBegin(int, int);

    std::deque<Product> calculatePath(
        std::unordered_map<Product*, std::deque<Product>> graph,
        std::deque<Product>& productList,
        Product& startLocation,
        Product& endLocation
        );

    std::deque<Product> singleProductPath(
        Product& product, 
        Product& startLocation,
        Product& endLocation
        );


    std::deque<std::tuple<float,float>> STraversal(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation
            );

    std::tuple<float,float> getCurrentPosition(void);
    void setCurrentPosition(std::tuple<float,float>&);

    double distanceBetweenProductsEuclidean(Product& product1, Product& product2);

    std::deque<Product> getPath(void);
    QVector <QPointF> displayPath(void);
    QVector <std::string> pathAnnotation(std::deque<Product>& path);

};
