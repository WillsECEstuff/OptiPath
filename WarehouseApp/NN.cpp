#include "PathFinder.h"

/**
 * @brief	Branch and Bound Algorithm
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
                std::cout<<"Vertex :"<<j<<std::endl;
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
                std::cout<<visitedCount<<"  "<<productList.size()-1<<std::endl;
                break;
            }
        }

        for(auto it = points.begin();it!=points.end();++it) {
            //pointsToDisplay.push_back(QPointF(std::get<0>(*it) * TILE_SIZE/SCALE,std::get<1>(*it)  * TILE_SIZE/SCALE));
            pointsFinished.push_back(QPointF(std::get<0>(*it), std::get<1>(*it)));
            pathLength += distanceBetweenPointsEuclidean(*(it+1),*it);
        }

        points.push_back(std::make_tuple(endLocation.getXPosition(),endLocation.getYPosition(),"-1"));
        return pointsFinished;
}



