/*****************************************************************//**
 * @file   AdjacencyMatrix.cpp
 * @brief  This source file contains the definitions for AdjacencyMatrix.h
 * 
 * @author Abinav
 * @date   October 2020
 *********************************************************************/

#include "AdjacencyMatrix.h"

/**
 * @brief	This is the defualt constructor for the AdjacencyMatrix object. 
 */
AdjacencyMatrix::AdjacencyMatrix(){}

/**
 * @brief	Will return the adjacency matrix. 
 */
std::unordered_map<std::string, std::deque<Product>> AdjacencyMatrix::getMatrix(void) {
    return graph;
}

/**
 * @brief	Will set the productList variable from given user input.
 */
void AdjacencyMatrix::setProductList(std::deque<Product> requestedProducts) {
    for(int i = 0; i < requestedProducts.size(); ++i) {
        productList.push_back(requestedProducts[i]);
    }
}

/**
 * @brief	Will setup graph from product list as an unordered_map.
 */
void AdjacencyMatrix::populateMatrix(void) {
    for(int i = 0;i<productList.size();++i) {
        for(int j = 0;j<productList.size();++j){
            if(i!=j){
                std::string productID = productList[i].getProductID();
                graph[productID].push_back(productList[j]);
            }
        }
    }
}
/**
 * @brief	Will display the adjacency matrix.
 */
void AdjacencyMatrix::displayMatrix(void) {
    std::unordered_map<std::string, std::deque<Product>> graph = getMatrix();
    for(auto& entry : graph) {
        std::cout<<entry.first<<"\t";
        for(auto& neighbor : entry.second) {
            std::cout<<neighbor.getProductID()<<"\t";
        }
        std::cout<<std::endl;
    }
}