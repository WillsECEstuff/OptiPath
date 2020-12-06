#include "PathFinder.h"
#include <unordered_set>
#include <algorithm>

void PathFinder::router(std::deque<Product>& productList,QVector<QPointF>& pointsFinished) {
    std::unordered_set<int> blocked;
    std::unordered_map<int,bool> visited;
    std::unordered_map<int,std::set<std::tuple<float,float,std::string>>> pickUpPoints;


    WarehouseMap* wMap = wMap->getInstance();
    json shelves = wMap->getShelves();

    auto productPoints = points;
    points.clear();
    pointsFinished.clear();

    //Get aisles to be visited
    for(auto& shelf : shelves.items()) {
        for(auto& product : productList) {
            if(product.getYPosition() == std::stoi(shelf.key())) {
                aislesToBeVisited.push_back(std::stoi(shelf.key()) + 1); //aisle "1" can access shelf "0"
            }
        }
    }
    // coordinates data strucure
    coordinates.resize(880,0);

    //Setup the initial vectors and check if they can be visited
    //If not add to blocked set
    for(int i = 0;i<40;++i) {
        for(int j = 0;j<22;++j) {
            int coord = j* 40 + i;
            visited[coord] = 0;
            if(j%2 == 1) coordinates[coord] = 1;
            else {
                if(std::find(shelves[std::to_string(j)]["occupied"].begin(),shelves[std::to_string(j)]["occupied"].end(),i)
                        != shelves[std::to_string(j)]["occupied"].end()) {
                    //std::cout<<"Blocked: "<<i<<" "<<j<<std::endl;
                    blocked.insert(coord);
                }
            }
        }
    }

    //Add pickup points for each product if they are valid. Only accessible from aisles
    for(int i = 1;i<(int)productPoints.size();++i) {
        //std::cout<<"Product :"<<productList[i].getXPosition()<<" "<<productList[i].getYPosition()<<std::endl;
        //std::cout<<"Product :"<<std::get<0>(productPoints[i])<<" "<<std::get<1>(productPoints[i])<<std::endl;
        int coord = ((int)std::get<1>(productPoints[i])*40 + (int)std::get<0>(productPoints[i]));

        if(blocked.find(coord+40) == blocked.end() && std::get<1>(productPoints[i]) +1 < 22) {
            pickUpPoints[i].insert(std::make_tuple(floor(std::get<0>(productPoints[i])),floor(std::get<1>(productPoints[i])+1),"-1"));
            pickUpPoints[i].insert(std::make_tuple(ceil(std::get<0>(productPoints[i])),ceil(std::get<1>(productPoints[i])+1),"-1"));
        }

        if(blocked.find(coord-40) == blocked.end() && std::get<1>(productPoints[i]) -1 >= 0) {
            pickUpPoints[i].insert(std::make_tuple(floor(std::get<0>(productPoints[i])),floor(std::get<1>(productPoints[i])+1),"-1"));
            pickUpPoints[i].insert(std::make_tuple(ceil(std::get<0>(productPoints[i])),ceil(std::get<1>(productPoints[i])-1),"-1"));

        }
    }

    int startIndex = std::get<1>(productPoints[0]) * 40 + std::get<0>(productPoints[0]);
    auto start = productPoints[0];
    float minDistance = distanceBetweenPointsEuclidean(start,productPoints[1]);
    minDistance = (float)INT_MAX;
    auto nextPoint = start;
    auto temp = start;

    //Add start location to points finished list
    points.push_back(std::make_tuple(std::get<0>(nextPoint),std::get<1>(nextPoint),"-1"));
    pointsFinished.push_back(QPointF(std::get<0>(nextPoint),std::get<1>(nextPoint)));


    for(int i = 1;i<(int)productPoints.size();++i) {
        std::cout<<"Product point to be visited "<<std::get<0>(productPoints[i])<<"  "<<std::get<1>(productPoints[i])<<std::endl;
        std::set<std::tuple<float,float,std::string>> visitedThisCycle;

        //Use this if diagonal traversal is required
        bool diagonalTraversal = false;

        //while(std::get<1>(nextPoint) != std::get<1>(productPoints[i]) - 1) {
        while(pickUpPoints[i].find(nextPoint) == pickUpPoints[i].end()) {
            auto tempPoint = nextPoint;
            visitedThisCycle.insert(nextPoint);
            //Right
            std::get<0>(nextPoint)++;
            if(blocked.find(startIndex + 1) == blocked.end() && std::get<0>(nextPoint) <= 40) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    std::cout<<minDistance<<std::endl;
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }
            //visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;

            //Left
            std::get<0>(nextPoint)--;
            std::get<0>(nextPoint)--;
            if(blocked.find(startIndex - 1) == blocked.end() && (std::get<0>(nextPoint)) >=0 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    std::cout<<minDistance<<std::endl;
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }
            //visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;

            //Top
            std::get<0>(nextPoint)++;
            std::get<1>(nextPoint)++;
            if(blocked.find(startIndex + 40) == blocked.end() && std::get<1>(nextPoint) < 22 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }
            //visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;

            //Down
            std::get<1>(nextPoint)--;
            std::get<1>(nextPoint)--;
            if(blocked.find(startIndex - 40) == blocked.end() && std::get<1>(nextPoint) >=0 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }
            //visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;

            if(diagonalTraversal) {
            //Left-Down
            std::get<1>(nextPoint)++;
            std::get<1>(nextPoint)--;
            std::get<0>(nextPoint)--;
            if(blocked.find(startIndex - 41) == blocked.end() && std::get<1>(nextPoint) >=0 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }

            //Right-Down
            std::get<0>(nextPoint)++;
            std::get<0>(nextPoint)++;
            if(blocked.find(startIndex - 39) == blocked.end() && std::get<1>(nextPoint) >=0 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }

            //Right-Top
            std::get<1>(nextPoint)++;
            std::get<1>(nextPoint)++;
            if(blocked.find(startIndex + 41) == blocked.end() && std::get<1>(nextPoint) >=0 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }

            //Left-Top
            std::get<0>(nextPoint)--;
            std::get<0>(nextPoint)--;
            if(blocked.find(startIndex + 39) == blocked.end() && std::get<1>(nextPoint) >=0 ) {
                std::cout<<"Index "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;
                if(distanceBetweenPointsEuclidean(nextPoint,productPoints[i]) < minDistance &&
                        visitedThisCycle.find(nextPoint) == visitedThisCycle.end()) {
                    visitedThisCycle.insert(nextPoint);
                    minDistance = distanceBetweenPointsEuclidean(nextPoint,productPoints[i]);
                    temp = nextPoint;
                    visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
                }
            }
            diagonalTraversal = false;
            }
            nextPoint = temp;
            points.push_back(std::make_tuple(std::get<0>(nextPoint),std::get<1>(nextPoint),"-1"));
            pointsFinished.push_back(QPointF(std::get<0>(nextPoint),std::get<1>(nextPoint)));

            //Change start index for next iteration
            startIndex = std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint);
            std::cout<<"Next point to be visited : "<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<std::endl;

            //To avoid repetition in case no good option is available
            //Try to increment/decrement X and Y coordinates
            if(nextPoint == tempPoint) {

                //X++
                if(blocked.find(startIndex+1) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint)+1,std::get<1>(nextPoint),"-1")) == visitedThisCycle.end()) {
                    std::get<0>(nextPoint) += 1;
                    std::cout<<"Same point so incrementing X ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                }

                //X--
                else if(blocked.find(startIndex-1) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint)-1,std::get<1>(nextPoint),"-1")) == visitedThisCycle.end()) {
                    std::get<0>(nextPoint) -= 1;
                    std::cout<<"Same point so decrementing X ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                }

                //Y--
                else if(blocked.find(startIndex-40) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint),std::get<1>(nextPoint)-1,"-1")) == visitedThisCycle.end()) {
                    std::get<1>(nextPoint) -= 1;
                    std::cout<<"Same point so decrementing Y ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                }

                //Y++
                else if(blocked.find(startIndex+40) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint),std::get<1>(nextPoint)+1,"-1")) == visitedThisCycle.end()) {
                    std::get<1>(nextPoint) += 1;
                    std::cout<<"Same point so incrementing Y ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                }

                //Newly added
                //X++ Y++
                else if(blocked.find(startIndex+41) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint)+1,std::get<1>(nextPoint)+1,"-1")) == visitedThisCycle.end()) {
                    std::get<1>(nextPoint) += 1;
                    std::get<0>(nextPoint) += 1;
                    std::cout<<"Same point so changing X and Y ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                    diagonalTraversal = true;
                }

                //X-- Y--
                else if(blocked.find(startIndex-41) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint)-1,std::get<1>(nextPoint)-1,"-1")) == visitedThisCycle.end()) {
                    std::get<1>(nextPoint) -= 1;
                    std::get<0>(nextPoint) -= 1;
                    std::cout<<"Same point so changing X and Y ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                    diagonalTraversal = true;
                }

                //X-- Y++
                else if(blocked.find(startIndex+39) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint)-1,std::get<1>(nextPoint)+1,"-1")) == visitedThisCycle.end()) {
                    std::get<1>(nextPoint) += 1;
                    std::get<0>(nextPoint) -= 1;
                    std::cout<<"Same point so changing X and Y ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                    diagonalTraversal = true;
                }

                //X++ Y--
                else if(blocked.find(startIndex-39) == blocked.end() &&
                        visitedThisCycle.find(std::make_tuple(std::get<0>(nextPoint)+1,std::get<1>(nextPoint)-1,"-1")) == visitedThisCycle.end()) {
                    std::get<1>(nextPoint) -= 1;
                    std::get<0>(nextPoint) += 1;
                    std::cout<<"Same point so changing X and Y ("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<std::endl;
                    diagonalTraversal = true;
                }
                //visited[std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint)] = 1;
            }
            else {
                std::cout<<"Not the same point "<<"("<<std::get<0>(nextPoint)<<"  "<<std::get<1>(nextPoint)<<")"<<"("<<std::get<0>(tempPoint)<<"  "<<std::get<1>(tempPoint)<<")"<<std::endl;
            }
            minDistance = (float)INT_MAX;
            //Change start index for next iteration
            startIndex = std::get<1>(nextPoint) * 40 + std::get<0>(nextPoint);
        }
        std::cout<<"Product "<<std::get<0>(productPoints[i])<<" "<<std::get<1>(productPoints[i])<<" visited!!"<<std::endl;
        visitedThisCycle.clear();
        for(auto entry : visited) entry.second = 0;
    }

    //Add end point to the traversal
    pointsFinished.push_back(QPointF(std::get<0>(productPoints.back()),std::get<1>(productPoints.back())));
    points.push_back(std::make_tuple(std::get<0>(productPoints.back()),std::get<1>(productPoints.back()),"-1"));
}
/**
 * @brief	NN Algorithm
 *
 * @param	productList		List of products to be picked up
 * @param	startLocation   Start location deaulted to (0,1)
 * @param   endLocation     End location defaulted to (0,1)
 *
 * @return  Ordered set of points to be visited
 */

QVector<QPointF> PathFinder :: NNAlgorithm(
        std::deque<Product>& productList,
        Product& startLocation,
        Product& endLocation,
        float userTimer
        ) {

        //QVector<QPointF> points;
        QVector<QPointF> pointsFinished;
        std::unordered_map<int,Product*> indexToProduct;
        productList.push_front(startLocation);

        std::vector<std::vector<int> > matrix(productList.size(),std::vector<int>(productList.size()));
        std::vector<int> visited(productList.size(),0);

        int currVert = 0;

        for(int i = 0;i<(int)productList.size();++i) {
            indexToProduct[i] = &productList[i];
        }

        for(int i = 0;i<(int)matrix.size();++i) {
            for(int j = 0;j<(int)matrix[0].size();++j) {
                matrix[i][j] = distanceBetweenProductsEuclidean(*indexToProduct[i],*indexToProduct[j]);
                std::cout<<matrix[i][j]<<"  ";
            }
            std::cout<<std::endl;
        }

        while(true) {
            std::cout<<"Visiting :"<<currVert<<std::endl;
            int minDist = INT_MAX;
            int minVert = currVert;
            int visitedCount = 0;
            visited[currVert] = 1;
            //points.push_back(QPointF(productList[currVert].getXPosition() * TILE_SIZE/SCALE,productList[currVert].getYPosition() * TILE_SIZE/SCALE));
            points.push_back(std::make_tuple(productList[currVert].getXPosition(),productList[currVert].getYPosition(),"-1"));
            for(int j = 0;j<(int)matrix[currVert].size();++j) {
                //std::cout<<"Vertex :"<<j<<std::endl;
                if(visited[j] != 1 && distanceBetweenProductsEuclidean(*indexToProduct[currVert],*indexToProduct[j]) < minDist) {
                    minDist = distanceBetweenProductsEuclidean(*indexToProduct[currVert],*indexToProduct[j]);
                    minVert = j;
                }
                else if(visited[j] == 1 && currVert!=j){
                    visitedCount++;
                }

                else if(visited[j] != 1) {
                    currVert = j;
                    continue;
                }
            }
            currVert = minVert;
            if(visitedCount == (int)productList.size()-1) {
                //std::cout<<visitedCount<<"  "<<productList.size()-1<<std::endl;
                break;
            }
        }

        points.push_back(std::make_tuple(endLocation.getXPosition(),endLocation.getYPosition(),"-1"));

        for(auto it = points.begin();it!=points.end();++it) {
            //pointsToDisplay.push_back(QPointF(std::get<0>(*it) * TILE_SIZE/SCALE,std::get<1>(*it)  * TILE_SIZE/SCALE));
            pointsFinished.push_back(QPointF(std::get<0>(*it), std::get<1>(*it)));
            pathLength += distanceBetweenPointsEuclidean(*(it+1),*it);
        }
        router(productList,pointsFinished);

        return pointsFinished;
}



