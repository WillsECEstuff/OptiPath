#include "branchandbound.h"

double BranchAndBound::distanceBetweenProductsEuclidean(Product& product1, Product& product2) {
    double distance = sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) +
                        pow(product1.getYPosition() - product2.getYPosition(),2));
    //std::cout<<"Distance between "<<product1.getProductID()<<" and "<<product2.getProductID()<<" = "<<distance<<std::endl;
    return distance;
}

void BranchAndBound :: copyToFinal(std::vector<int>& currPath)
{
    for (int i=0; i<(int)currPath.size(); i++)
        finalPath[i] = currPath[i];
    finalPath[currPath.size()-1] = currPath[0];
}

int BranchAndBound :: firstMin(std::vector<std::vector<int> >& matrix, int i)
{
    int min = INT_MAX;
    for (int k=0; k<(int)matrix[0].size(); k++)
        if (matrix[i][k]<min && i != k)
            min = matrix[i][k];
    return min;
}

int BranchAndBound :: secondMin(std::vector<std::vector<int> >& matrix, int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<(int)matrix[0].size(); j++)
    {
        if (i == j)
            continue;

        if (matrix[i][j] <= first)
        {
            second = first;
            first = matrix[i][j];
        }
        else if (matrix[i][j] <= second &&
                 matrix[i][j] != first)
            second = matrix[i][j];
    }
    return second;
}

void BranchAndBound :: TSPRec(std::vector<std::vector<int> >& matrix, int currBound, int curr_weight,
            int level, std::vector<int>& currPath, std::deque<Product>& productList)
{
    if (level== (int)productList.size())
    {

        if (matrix[currPath[level-1]][currPath[0]] != 0)
        {

            int currRes = curr_weight +
                    matrix[currPath[level-1]][currPath[0]];

            if (currRes < minPathLength)
            {
                copyToFinal(currPath);
                minPathLength = currRes;
            }
        }
        return;
    }

    for (int i=0; i<(int)currPath.size()-1; i++)
    {
        if (matrix[currPath[level-1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = currBound;
            curr_weight += matrix[currPath[level-1]][i];

            if (level==1)
              currBound -= ((firstMin(matrix, currPath[level-1]) +
                             firstMin(matrix, i))/2);
            else
              currBound -= ((secondMin(matrix, currPath[level-1]) +
                             firstMin(matrix, i))/2);

            if (currBound + curr_weight < minPathLength)
            {
                currPath[level] = i;
                visited[i] = true;

                TSPRec(matrix, currBound, curr_weight, level+1,
                       currPath,productList);
                std::cout<<"After TSPRec : "<<level<<std::endl;
            }

            curr_weight -= matrix[currPath[level-1]][i];
            currBound = temp;

            // Also reset the visited array
            for(int i = 0;i<(int)productList.size();++i) {
                visited[i] = false;
            }
            for (int j=0; j<=level-1; j++)
                visited[currPath[j]] = true;
        }
    }
}


/**
 * @brief	Branch and Bound Algorithm
 *
 * @param	productList		List of products to be picked up
 * @param	startLocation   Start location deaulted to (0,1)
 * @param   endLocation     End location defaulted to (0,1)
 *
 * @return  Ordered set of points to be visited
 */

QVector<QPointF> BranchAndBound :: branchAndBound(
        std::deque<Product>& productList,
        Product& startLocation,
        Product& endLocation
        ) {

        QVector<QPointF> points;
        std::vector<int> currPath(productList.size()+1,-1);
        finalPath.resize(productList.size() + 1);
        visited.assign(productList.size() + 1,0);

        std::vector<std::vector<int> > matrix(productList.size(),std::vector<int>(productList.size()));

        for(int i = 0;i<(int)productList.size();++i) {
            indexToProduct[i] = &productList[i];
        }

        for(int i = 0;i<(int)matrix.size();++i) {
            for(int j = 0;j<(int)matrix[0].size();++j) {
                matrix[i][j] = distanceBetweenProductsEuclidean(*indexToProduct[i],*indexToProduct[j]);
            }
        }

        int currBound = 0;

        for (int i=0; i<(int)productList.size(); i++)
            currBound += (firstMin(matrix, i) +
                           secondMin(matrix, i));

        currBound = (currBound & 1)? currBound/2 + 1 :
                                     currBound/2;


        visited[0] = true;
        currPath[0] = 0;

        TSPRec(matrix, currBound, 0, 1, currPath, productList);
        std::cout<<"Finished branch and bound"<<std::endl;
        for(int i = 0;i<(int)productList.size();++i) {
            points.push_back(QPointF(productList[i].getXPosition() * TILE_SIZE/SCALE,productList[i].getYPosition() * TILE_SIZE/SCALE));
        }
        return points;
}



