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

enum Compass { North = 0, NorthWest, West, SouthWest, South, SouthEast, 
    East, NorthEast, Stay};

class PathFinder {
    private:
    const std::vector<std::string> dir = { "North", "NorthWest", "West", 
        "SouthWest", "South", "SouthEast", "East", "NorthEast", "Stay"};
    double pathLength;
    std::tuple<float,float> currentPosition;
    std::vector<int> aislesToBeVisited;
    std::deque<std::tuple<float,float,std::string>> points;
    std::deque<Product> path;
    std::vector<int> coordinates;
    const std::string NOT_PRODUCT = "-1";
    const float TILE_SIZE = 30;
    const float SCALE = 5;

    Compass getHeading(std::tuple<float, float, std::string> p1,
        std::tuple<float, float, std::string> p2);

    public:
    int findMaxEnd(int, int);
    int findMinBegin(int, int);

    std::vector<int> nextOpenAisle(Product& product1, Product& product2);

    QVector<QPointF> NNAlgorithm(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation,
            float userTimer
            );

    QVector<QPointF> calculatePath(
        std::deque<Product>& productList,
        Product& startLocation,
        Product& endLocation,
        float userTimer
        );

    std::deque<Product> singleProductPath(
        Product& product, 
        Product& startLocation,
        Product& endLocation
        );

    QVector<QPointF> STraversalGaps(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation
            );

    QVector<QPointF> STraversal(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation,
            float userTimer
            );

    QVector<QPointF> ReturnTraversal(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation,
            float userInput
            );

    QVector<QPointF> HybridTraversal(
            std::deque<Product>& productList,
            Product& startLocation,
            Product& endLocation
            );
    //Branch and bound stuff

    void router(std::deque<Product>& productList,QVector<QPointF>&,float userTimer);



    std::tuple<float,float> getCurrentPosition(void);
    void setCurrentPosition(std::tuple<float,float>&);

    double distanceBetweenPointsEuclidean(std::tuple<float,float,std::string>&, std::tuple<float,float,std::string>&);
    double distanceBetweenProductsEuclidean(Product& product1, Product& product2);
    std::tuple<double, int, int> distanceBetweenProductsTaxicab(Product& product1, Product& product2);

    std::deque<Product> getPath(void);
    QVector <QPointF> displayPath(void);

    QVector <std::string> pathAnnotation();
    QVector <std::string> oldAnnotation(std::deque<Product>& path);

    std::deque<std::tuple<float, float, std::string>> getPoints();
};
