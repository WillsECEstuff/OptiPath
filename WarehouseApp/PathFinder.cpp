#include "PathFinder.h"

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

std::deque<std::string> PathFinder::calculatePath(
    std::unordered_map<std::string, std::deque<Product>> graph, 
    std::tuple<float,float> startLocation,
    std::tuple<float,float> endLocation
    ) {
    //startLocation = std::make_tuple(0,0);
    for(auto& element : graph) {
        distance[element.first] = INT_MAX;
        visited[element.first] = 0;
    }
    
}

std::deque<std::string> PathFinder::singleProductPath(
    Product product, 
    std::tuple<float,float> startLocation,
    std::tuple<float,float> endLocation
    ) {
    //startLocation = std::make_tuple(0,0);
    path.push_back("Start");
    path.push_back(product.getProductID());
    path.push_back("End");
    return path;
}