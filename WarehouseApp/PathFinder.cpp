#include "PathFinder.h"

float PathFinder::distanceBetweenProducts(Product& product1, Product& product2) {
    return sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) + pow(product1.getYPosition() - product2.getYPosition(),2));
}

std::string PathFinder::minDistance() {
    int min = INT_MAX;
    std::string minProductID;
    for(auto& entry : visited) {
        std::string productID = entry.first;
        bool checkVisit = entry.second; 
        if(checkVisit == false && distance[productID] <= min) {
            min = distance[productID];
            minProductID = productID;
        }
    }
    return minProductID;
}


//std::deque<std::string> PathFinder::calculatePath(
    float PathFinder::calculatePath(
    std::unordered_map<Product*, std::deque<Product>>& graph,
    std::deque<Product> productList, 
    Product& startLocation,
    Product& endLocation
    ) {
    //startLocation = std::make_tuple(0,0);
    //endLocation = std::make_tuple(40,20);
    /*
    std::vector<Product> vertices;
    for(auto& entry : graph) {
        if((entry.first)->getProductID() != startLocation.getProductID())
            vertices.push_back(*(entry.first));
    }
    
    int minPath = INT_MAX;
    do {
        float currentPathWeight = 0;
        Product k = startLocation;
        
        for(auto& entry : graph) {
            Product next = *(entry.first); 
            currentPathWeight += distanceBetweenProducts(k,next);
            k = next; 
        }
        
        currentPathWeight += distanceBetweenProducts(k,endLocation);
    } while(next_permutation(vertices.begin(),vertices.end()));
    return minPath;
    */
}


std::deque<std::string> PathFinder::singleProductPath(
    Product& product, 
    std::tuple<float,float> startLocation,
    std::tuple<float,float> endLocation
    ) {
    //startLocation = std::make_tuple(0,0);
    path.push_back("Start");
    path.push_back(product.getProductID());
    path.push_back("End");
    return path;
}