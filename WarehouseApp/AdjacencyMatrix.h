/*****************************************************************//**
 * @file   AdjacencyMatrix.h
 * @brief  This header includes the AdjacencyMatrix. The AdjacencyMatrix class 
 *			contains members: productList and graph. The productList is a vector of 
            products for which the best route has to be figure out. The graph is
            an unordered_map with productID as the key and vector of products as
            its value - This represents the adjacency matrix of the products. 
 *			
 * @author Abinav
 * @date   October 2020
 *********************************************************************/


#include <iostream>
#include <unordered_map>
#include <string>
#include <deque>

#include "Database.h"
#include "Product.h"

class AdjacencyMatrix {
    private:
        std::deque<Product> productList;
        std::unordered_map<std::string, std::deque<Product>> graph;

    public:
        AdjacencyMatrix();
        void populateMatrix(void);
        void setProductList(std::deque<Product> requestedProducts);
        std::deque<std::string> calculateShortestPath(void);
        void displayMatrix(void);

        std::unordered_map<std::string, std::deque<Product>> getMatrix(void);
};