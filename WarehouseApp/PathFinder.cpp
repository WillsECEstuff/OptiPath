#include "PathFinder.h"

float PathFinder::distanceBetweenProducts(Product& product1, Product& product2) {
    float distance = sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) + pow(product1.getYPosition() - product2.getYPosition(),2));
    //std::cout<<"Distance between "<<product1.getProductID()<<" and "<<product2.getProductID()<<" = "<<distance<<std::endl;
    return sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) + pow(product1.getYPosition() - product2.getYPosition(),2));
}

std::deque<Product> PathFinder::calculatePath(
    std::unordered_map<Product*, std::deque<Product>> graph,
    std::deque<Product> productList, 
    Product startLocation,
    Product endLocation
    ) {
        std::vector<Product> vertices;
        for(auto& entry : graph) {
            if((entry.first)->getProductID() != startLocation.getProductID())
                vertices.push_back(*(entry.first));
        }
    
        float minPath = INT_MAX;
        do {
            float currentPathWeight = 0;
            Product k = startLocation;
            std::deque<Product> currPath;
            currPath.push_back(startLocation);
            for(auto entry : vertices) {
                Product next = entry;
                currentPathWeight += distanceBetweenProducts(k,next);
                k = next; 
                currPath.push_back(next);
            }
            currentPathWeight += distanceBetweenProducts(k,endLocation);
            currPath.push_back(endLocation);
            if(currentPathWeight < minPath){
                path = currPath;
                minPath = currentPathWeight;
            }
        } while(next_permutation(vertices.begin(),vertices.end(), [](Product& a, Product& b) -> bool 
        {
            return a.getProductID()< b.getProductID();
        }));
    return path;  
}

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

void PathFinder::displayPath(void) {
    for(auto& vertex : path) {
        std::cout<<vertex.getProductID()<<"->";
    }
}