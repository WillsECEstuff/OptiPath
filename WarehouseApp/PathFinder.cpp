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

std::deque<std::string> PathFinder::calculatePath(
    std::unordered_map<std::string, std::deque<Product>>& graph, 
    std::tuple<float,float> startLocation,
    std::tuple<float,float> endLocation
    ) {
    //startLocation = std::make_tuple(0,0);
    //endLocation = std::make_tuple(40,20);
    for(auto& element : graph) {
        distance[element.first] = INT_MAX;
        visited[element.first] = 0;
    }
    /*
    distance["startLocation"] = 0;
    for(int i = 0;i<graph.size() -1; ++i) {
        std::string u = minDistance(distance,visited);
        visited[u] = true;
        for(auto& neighbor : graph[u]) {
            if (!visited[neighbor] && distance[u] != INT_MAX && distance[u] + distanceBetweenProducts() < distance[neighbor]) {
                distance[neighbor] = distance[u] + graph[u][v]; 
            } 
        }
    }
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