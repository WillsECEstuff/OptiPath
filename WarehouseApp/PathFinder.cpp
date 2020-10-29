/*********************************************************************
 * @file   PathFinder.cpp
 * @brief  This source file contains the definitions for PathFinder.h
 * 
 * @author Abinav
 * @date   October 2020
 *********************************************************************/

#include "PathFinder.h"
#include <QVector>
#include <QPointF>


/**
 * @brief	Calculates distance between two products on the warehouse. 
            Takes two Products as arguments.
 * 
 * @param	product1		product1 is a product that will indicate the 
 *					        starting product
 * @param	product2		product1 is a product that will indicate the 
                            ending product
 */
double PathFinder::distanceBetweenProducts(Product& product1, Product& product2) {
    double distance = sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) +
                        pow(product1.getYPosition() - product2.getYPosition(),2));
    //std::cout<<"Distance between "<<product1.getProductID()<<" and "<<product2.getProductID()<<" = "<<distance<<std::endl;
    return sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) + 
                pow(product1.getYPosition() - product2.getYPosition(),2));
}

/**
 * @brief	Finds the most optimal path the user must take
 * 
 * @param   graph           Adjacency matrix of the products
 * @param   productList     List of products to be picked up
 * @param	startLocation   Take in the start location from the user
 * @param	endLocation		Takes in the end location from the user
 */
std::deque<Product> PathFinder::calculatePath(
    std::unordered_map<Product*, std::deque<Product>> graph,
    std::deque<Product> productList, 
    Product startLocation,
    Product endLocation
    ) {
        long numItr = 0;
        std::vector<Product> vertices;
        for(auto& entry : graph) {
            if((entry.first)->getProductID() != startLocation.getProductID())
                vertices.push_back(*(entry.first));
        }

        std::sort(vertices.begin(),vertices.end(),[](Product& a, Product& b) -> bool
        {
            return a.getProductID()< b.getProductID();
        });

        pathLength = (double)INT_MAX;
        do {
            double currentPathLength = 0;
            Product k = startLocation;
            std::deque<Product> currPath;
            currPath.push_back(startLocation);
            for(auto entry : vertices) {
                Product next = entry;
                currentPathLength += distanceBetweenProducts(k,next);
                k = next; 
                currPath.push_back(next);
            }
            currentPathLength += distanceBetweenProducts(k,endLocation);
            currPath.push_back(endLocation);
            if(currentPathLength < pathLength){
                path = currPath;
                pathLength = currentPathLength;
            }
            numItr++;
        } while(next_permutation(vertices.begin(),vertices.end(), [](Product& a, Product& b) -> bool 
        {
            return a.getProductID()< b.getProductID();
        }));
        std::cout<<"Number of paths evaluated = "<<numItr<<std::endl;
    return path;  
}

/**
 * @brief	To be used if only one product is to be picked
 * 
 * @param   product         Product to be picked up
 * @param	startLocation   Take in the start location from the user
 * @param	endLocation		Takes in the end location from the user
 */

std::deque<Product> PathFinder::singleProductPath(
    Product& product, 
    Product startLocation,
    Product endLocation
    ) {
    //startLocation = std::make_tuple(0,0);
    path.push_back(startLocation);
    path.push_back(product);
    path.push_back(endLocation);
    return path;
}

/**
 * @brief	Display the path in textual human readable format along
 *          with total path length
 * 
 * @param   product         Product to be picked up
 * @param	startLocation   Take in the start location from the user
 * @param	endLocation		Takes in the end location from the user
 */
QVector <QPointF> PathFinder::displayPath(void) { // was void return type
    QVector <QPointF> routeprinter;

    for(auto& vertex : path) {
        std::cout<<vertex.getProductID()<<"->";
        routeprinter.append(QPointF(vertex.getXPosition() * TILE_SIZE/SCALE, vertex.getYPosition() * TILE_SIZE/SCALE));
    }
    std::cout<<std::endl;
    std::cout<<"Minimum path length = "<< pathLength<<std::endl;

    return routeprinter;
}

std::deque<Product> PathFinder::getPath(void) {
    return path;
}

QVector <std::string> PathFinder::pathAnnotation(std::deque<Product>& path) {
    QVector <std::string> instructions;
    std::stringstream xStream, yStream;

    xStream << std::fixed << std::setprecision(2) << path[0].getXPosition();
    yStream << std::fixed << std::setprecision(2) << path[0].getYPosition();

    std::string instruction = "Start at start location present in (" + xStream.str()
                                    + ',' + yStream.str() + ")";

    xStream.str(""); yStream.str("");

    instructions.append(instruction);
    for(unsigned int i = 1;i < path.size();++i) {
        xStream << std::fixed << std::setprecision(2) << path[i].getXPosition();
        yStream << std::fixed << std::setprecision(2) << path[i].getYPosition();

        instruction = "go to product " + path[i].getProductID() + " at (" +
                xStream.str() +"," + yStream.str() + ")";

        xStream.str(""); yStream.str("");

        instructions.append(instruction);
    }

    xStream << std::fixed << std::setprecision(2) << path[path.size()-1].getXPosition();
    yStream << std::fixed << std::setprecision(2) << path[path.size()-1].getYPosition();

    instruction = "Drop the products off at end location in (" + xStream.str()
            + ',' + yStream.str() + ")";

    xStream.str(""); yStream.str("");

    instructions.append(instruction);
    return instructions;
}
