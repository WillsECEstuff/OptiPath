/*********************************************************************
 * @file   PathFinder.cpp
 * @brief  This source file contains the definitions for PathFinder.h
 * 
 * @author Abinav
 * @date   October 2020
 *********************************************************************/

#include "PathFinder.h"
#include <chrono>

/**
 * @brief	Calculates distance between two points on the warehouse.
            Takes two points as arguments.
 *
 * @param	point1		point1 is a location that will indicate the
 *					        starting point
 * @param	point2		point2 is a location that will indicate the
                            ending point
 * @return  Euclidean distance between points
 */

double PathFinder::distanceBetweenPointsEuclidean(std::tuple<float,float,std::string>& point1,
                                                  std::tuple<float,float,std::string>& point2) {

    return sqrt(pow(std::get<0>(point1) - std::get<0>(point2),2) +
                pow(std::get<1>(point1) - std::get<1>(point2),2));
}

/**
 * @brief	Calculates distance between two products on the warehouse. 
            Takes two Products as arguments.
 * 
 * @param	product1		product1 is a product that will indicate the 
 *					        starting product
 * @param	product2		product1 is a product that will indicate the 
                            ending product
 * @return  Euclidean distance between products
 */
double PathFinder::distanceBetweenProductsEuclidean(Product& product1, Product& product2) {
    double distance = sqrt(pow(product1.getXPosition() - product2.getXPosition(),2) +
                        pow(product1.getYPosition() - product2.getYPosition(),2));
    //std::cout<<"Distance between "<<product1.getProductID()<<" and "<<product2.getProductID()<<" = "<<distance<<std::endl;
    return distance;
}

std::tuple<double, int, int> distanceBetweenProductsTaxicab(Product& product1, Product& product2) { // returns tuple (distance, left/right, up/down), where -1 = left or down
    double deltaX = product1.getXPosition() - product2.getXPosition();
    double deltaY = product1.getYPosition() - product2.getYPosition();
    double distance = abs(deltaX) + abs(deltaY);

    std::tuple<double, int, int> taxiDist;

    int leftright = 1, updown = 1;

    if (deltaX < 0) {
        leftright = -1;
    }

    if (deltaY < 0) {
        updown = -1;
    }

    taxiDist = std::make_tuple(distance,leftright,updown);

    return taxiDist;
}

/**
 * @brief	Calculates the maximum distance to be traveled towards right
 *
 * @param	shelfStart		Indicates the starting shelf number
 * @param	shelfEnd		Indicates the ending shelf number
 *
 * @return  Maxmimum X coordinate to be traveled aling the aisle
 */

int PathFinder::findMaxEnd(int shelfStart, int shelfEnd) {
    WarehouseMap* wMap = wMap->getInstance();
    json shelves = wMap->getShelves();
    int max = 0;
    for(int i = shelfStart; i<=shelfEnd; i+=2) {
        std::string aisleCount = std::to_string(i);
        int endCoord = static_cast<int>(shelves[aisleCount]["end"]) + 1;
        max = max > std::ceil(endCoord) ? max : std::ceil(endCoord);
    }
    return max;
}

/**
 * @brief	Calculates the maximum distance to be traveled towards left
 *
 * @param	shelfStart		Indicates the starting shelf number
 * @param	shelfEnd		Indicates the ending shelf number
 *
 * @return  Minimum X coordinate to be traveled aling the aisle
 */

int PathFinder::findMinBegin(int shelfStart, int shelfEnd) {
    WarehouseMap* wMap = wMap->getInstance();
    json shelves = wMap->getShelves();
    int min = INT_MAX;
    for(int i = shelfStart; i<=shelfEnd; i+=2) {
        std::string aisleCount = std::to_string(i);
        int beginCoord = static_cast<int>(shelves[aisleCount]["begin"]) - 1;
        min = min < std::floor(beginCoord) ? min : std::floor(beginCoord);
    }
    return min;
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


int PathFinder :: firstMin(std::vector<std::vector<int> >& matrix, int i)
{
    int min = INT_MAX;
    for (int k=0; k<(int)matrix.size(); k++)
        if (matrix[i][k]<min && i != k)
            min = matrix[i][k];
    return min;
}

int PathFinder :: secondMin(std::vector<std::vector<int> >& matrix, int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<(int)matrix.size(); j++)
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

void PathFinder :: TSPRec(std::vector<std::vector<int> >& matrix, int curr_bound, int curr_weight,
            int level, std::vector<int>& currPath)
{

    if (level== (int)matrix.size())
    {

        if (matrix[currPath[level-1]][currPath[0]] != 0)
        {

            int curr_res = curr_weight +
                    matrix[currPath[level-1]][currPath[0]];

            if (curr_res < minPathLength)
            {
                copyToFinal(currPath);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i=0; i<N; i++)
    {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (adj[currPath[level-1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = curr_bound;
            curr_weight += adj[currPath[level-1]][i];

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level==1)
              curr_bound -= ((firstMin(adj, currPath[level-1]) +
                             firstMin(adj, i))/2);
            else
              curr_bound -= ((secondMin(adj, currPath[level-1]) +
                             firstMin(adj, i))/2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res)
            {
                currPath[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                TSPRec(adj, curr_bound, curr_weight, level+1,
                       currPath);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= adj[currPath[level-1]][i];
            curr_bound = temp;

            // Also reset the visited array
            memset(visited, false, sizeof(visited));
            for (int j=0; j<=level-1; j++)
                visited[currPath[j]] = true;
        }
    }
}

QVector<QPointF> PathFinder :: branchAndBound(
        std::deque<Product>& productList,
        Product& startLocation,
        Product& endLocation
        ) {

        std::vector<int> currPath(productList.size()+1,-1);
        std::vector<std::vector<int> > matrix(productList.size(),std::vector<int>(productList.size()));

        for(int i = 0;i<(int)matrix.size();++i) {
            for(int j = 0;i<(int)matrix[0].size();++i) {
                matrix[i][j] = distanceBetweenProductsEuclidean(*indexToProduct[i],*indexToProduct[j]);
            }
        }

        int currBound = 0;
        for(int i  = 0;i<(int)productList.size();++i) {
            visited[&productList[i]] = false;
            indexToProduct[i] = &productList[i];
        }

        for (int i=0; i<(int)matrix.size(); i++)
            currBound += (firstMin(matrix, i) +
                           secondMin(matrix, i));

        currBound = (currBound&1)? currBound/2 + 1 :
                                     currBound/2;


        visited[indexToProduct[0]] = true;
        currPath[0] = 0;

        TSPRec(matrix, currBound, 0, 1, currPath);
}



/**
 * @brief	Navigates along the warehouse aisles in an S shape
 *
 * @param	productList		List of products to be picked up
 * @param	startLocation   Start location deaulted to (0,1)
 * @param   endLocation     End location defaulted to (0,1)
 *
 * @return  Ordered set of points to be visited
 */

QVector<QPointF> PathFinder::STraversal(
        std::deque<Product>& productList,
        Product& startLocation,
        Product& endLocation
        ) {

        std::cout << "Pathfinder begin" << std::endl;
        int traversalOrder = 1; //1 -> left to right, 0-> right to left
        QVector<QPointF> pointsToDisplay;
        std::unordered_map<int, std::vector<Product>> aisleProductMap;
        auto start = std::chrono::high_resolution_clock::now();

        WarehouseMap* wMap = wMap->getInstance();
        currentPosition = startLocation.getPositionTuple();

        std::cout << "starting current: " << std::get<0>(currentPosition) << " " << std::get<1>(currentPosition) << std::endl;

        points.push_back(std::make_tuple(std::get<0>(currentPosition),std::get<1>(currentPosition),"-1"));
        json shelves = wMap->getShelves();

        //Add aisles to be visited
        for(auto& shelf : shelves.items()) {
            for(auto& product : productList) {
                if(product.getYPosition() == std::stoi(shelf.key())) {
                    aislesToBeVisited.push_back(std::stoi(shelf.key()) + 1); //aisle "1" can access shelf "0"
                    aisleProductMap[product.getYPosition()].push_back(product); // Add product to aisle key
                }
            }
        }

        std::cout<<"Aisles to be visited:"<<std::endl;
        std::sort(aislesToBeVisited.begin(),aislesToBeVisited.end());

        aislesToBeVisited.erase(std::unique(aislesToBeVisited.begin(), aislesToBeVisited.end()), aislesToBeVisited.end());
        for(auto& element : aislesToBeVisited) {
            std::cout<<element<<std::endl;
        }

        if(std::get<1>(currentPosition) != aislesToBeVisited.front()) {
            points.push_back(std::make_tuple(0,std::get<1>(currentPosition),"-1"));
            points.push_back(std::make_tuple(0,aislesToBeVisited.front(),"-1"));
        }

        //aislesToBeVisited is an ordered vector of aisles. (1,3,5,7,9.....)
        for(std::vector<int> :: iterator it = aislesToBeVisited.begin();it!=aislesToBeVisited.end()-1;++it) {
            int yCoord = *it;

            if(yCoord < 21) { //Make sure y coordinate does not exceed 19
                if(traversalOrder == 1) { // left to right

                    //Find the right most coordinate
                    int nextEnd = findMaxEnd(yCoord+1,*(it+1)-1);

                    //Add the Left most coordinate in the aisle
                    points.push_back(std::make_tuple(shelves[std::to_string(yCoord-1)]["begin"],yCoord,"-1"));

                    //Sort based on earliest product encountered in traversal
                    std::sort(aisleProductMap[yCoord-1].begin(),aisleProductMap[yCoord-1].end(),[](Product a, Product b) {
                        return a.getXPosition() < b.getXPosition();
                    });

                    //Add the product locations in the traversal
                    for(auto& product : aisleProductMap[yCoord-1]) {
                        points.push_back(std::make_tuple(product.getXPosition(),product.getYPosition(),product.getProductID()));
                    }

                    //Push the rightmost coordinate in the aisle
                    points.push_back(std::make_tuple(nextEnd,yCoord,"-1"));


                    //Travel to the next aisle
                    points.push_back(std::make_tuple(nextEnd,*(it+1),"-1"));

                    traversalOrder = 0;
                }
                else {//right to left

                    //Find the left most coordinate
                    int nextBegin = findMinBegin(yCoord+1,*(it+1)-1);

                    //Add the Right most coordinate in the aisle
                    points.push_back(std::make_tuple(shelves[std::to_string(yCoord-1)]["end"],yCoord,"-1"));

                    //Sort based on earliest product encountered in traversal
                    std::sort(aisleProductMap[yCoord-1].begin(),aisleProductMap[yCoord-1].end(),[](Product a, Product b) {
                        return a.getXPosition() > b.getXPosition();
                    });

                    //Add the product locations in the traversal
                    for(auto& product : aisleProductMap[yCoord-1]) {
                        points.push_back(std::make_tuple(product.getXPosition(),product.getYPosition(),product.getProductID()));
                    }

                    //Push the leftmost coordinate in the aisle
                    points.push_back(std::make_tuple(nextBegin,yCoord,"-1"));

                    //Travel to the next aisle
                    points.push_back(std::make_tuple(nextBegin,*(it+1),"-1"));

                    traversalOrder = 1;
                }
            }
        }

        //Visit the last aisle of products
       for(auto& product : aisleProductMap[aislesToBeVisited.back()-1]) {
            points.push_back(std::make_tuple(product.getXPosition(),product.getYPosition(),product.getProductID()));
       }

        //Go back to start location
        points.push_back(std::make_tuple(0,*(aislesToBeVisited.end()-1),"-1"));
        points.push_back(std::make_tuple(0,startLocation.getYPosition(),"-1"));
        points.push_back(std::make_tuple(startLocation.getXPosition(),startLocation.getYPosition(),"-1"));

        //Add points to display
        for(auto it = points.begin();it!=points.end()-1;++it) {
            pointsToDisplay.push_back(QPointF(std::get<0>(*it) * TILE_SIZE/SCALE,std::get<1>(*it)  * TILE_SIZE/SCALE));
            pathLength += distanceBetweenPointsEuclidean(*(it+1),*it);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"Total time taken for execution of baseline algorithm = "<<duration.count()<<" milliseconds"<<std::endl;
        std::cout<<"Total path length (approx) = "<<pathLength<<std::endl;
        return pointsToDisplay;
}

/**
 * @brief	Finds the most optimal path the user must take (O(n!) solution. Not used)
 * 
 * @param   graph           Adjacency matrix of the products
 * @param   productList     List of products to be picked up
 * @param	startLocation   Take in the start location from the user
 * @param	endLocation		Takes in the end location from the user
 *
 * @return  Ordered list of products in the path
 */
std::deque<Product> PathFinder::calculatePath(
    std::unordered_map<Product*, std::deque<Product>> graph,
    std::deque<Product>& productList,
    Product& startLocation,
    Product& endLocation
    ) {
        long numItr = 0;
        std::vector<Product> vertices;
        for(auto& entry : productList) {
            if(entry.getProductID() != startLocation.getProductID())
                vertices.push_back(entry);
        }

        //Sort the vector to make sure no permutation is missed
        std::sort(vertices.begin(),vertices.end(),[](Product& a, Product& b) -> bool
        {
            return a.getProductID()< b.getProductID();
        });

        pathLength = (double)INT_MAX;

        //Go through all permutations and find the lowest path length
        do {
            double currentPathLength = 0;
            Product k = startLocation;
            std::deque<Product> currPath;
            currPath.push_back(startLocation);
            for(auto entry : vertices) {
                Product next = entry;
                currentPathLength += distanceBetweenProductsEuclidean(k,next);
                k = next; 
                currPath.push_back(next);
            }
            currentPathLength += distanceBetweenProductsEuclidean(k,endLocation);
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
        //Print out number of paths evaluated
        std::cout<<"Number of paths evaluated = "<<numItr<<std::endl;
    return path;  
}

/**
 * @brief	To be used if only one product is to be picked
 * 
 * @param   product         Product to be picked up
 * @param	startLocation   Take in the start location from the user
 * @param	endLocation		Takes in the end location from the user
 *
 * @return  Ordered list of products in the path
 */

std::deque<Product> PathFinder::singleProductPath(
    Product& product, 
    Product& startLocation,
    Product& endLocation
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
 *
 * @return  Returns vector of points on the map
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

/**
 * @brief	Returns path for the user
 */

std::deque<Product> PathFinder::getPath(void) {
    return path;
}

/**
 * @brief	Stores instructions for user in a vector
 *
 * @param   path         Path output by the path finder
 *
 * @return  return instructions in user-readable format
 */

QVector <std::string> PathFinder::pathAnnotation() {
    QVector <std::string> instructions;
    std::stringstream xStream, yStream, distanceStream;

    xStream << std::fixed << std::setprecision(2) << std::get<0>(points[0]);
    yStream << std::fixed << std::setprecision(2) << std::get<1>(points[0]);

    std::string instruction = "Start at start location present in (" + xStream.str()
                                    + ',' + yStream.str() + ")";

    xStream.str(""); yStream.str("");

    instructions.append(instruction);
    for(unsigned int i = 1;i < points.size()-1;++i) {
        xStream << std::fixed << std::setprecision(2) << std::get<0>(points[i]);
        yStream << std::fixed << std::setprecision(2) << std::get<1>(points[i]);
        Compass c = getHeading(points[i - 1], points[i]);
        distanceStream << std::fixed << std::setprecision(2) <<
            distanceBetweenPointsEuclidean(points[i - 1], points[i]);

        if(std::get<2>(points[i]) != "-1") {
            if (c == Compass::Stay) {
                instruction = "Stay at product (" + xStream.str() + "," + yStream.str() + ")";
            }
            else {
                instruction = "Go " + distanceStream.str() + " units " + dir[c] + " to product " +
                    std::get<2>(points[i]) + " at (" + xStream.str() + "," + yStream.str() + ")";
            }
            
        }

        else {
            if (c == Compass::Stay) {
                instruction = "Stay at point (" + xStream.str() + "," + yStream.str() + ")";
            }
            else {
                instruction = "Go " + distanceStream.str() + " units " + dir[c] + " to point (" +
                    xStream.str() + "," + yStream.str() + ")";
            }
            
        }
        xStream.str(""); yStream.str(""); distanceStream.str("");

        instructions.append(instruction);
    }

    xStream << std::fixed << std::setprecision(2) << std::get<0>(points[points.size() - 1]);
    yStream << std::fixed << std::setprecision(2) << std::get<1>(points[points.size() - 1]);

    instruction = "Drop the products off at end location in (" + xStream.str()
            + ',' + yStream.str() + ")";

    xStream.str(""); yStream.str("");
    instructions.append(instruction);
    return instructions;
}

/**
 * @brief	Stores instructions for user in a vector
 *
 * @param   path         Path output by the path finder
 *
 * @return  return instructions in user-readable format
 */

QVector <std::string> PathFinder::oldAnnotation(std::deque<Product>& path) {
    QVector <std::string> instructions;
    std::stringstream xStream, yStream;

    xStream << std::fixed << std::setprecision(2) << path[0].getXPosition();
    yStream << std::fixed << std::setprecision(2) << path[0].getYPosition();

    std::string instruction = "Start at start location present in (" + xStream.str()
                                    + ',' + yStream.str() + ")";

    xStream.str(""); yStream.str("");

    instructions.append(instruction);
    for(unsigned int i = 1;i < path.size()-1;++i) {
        xStream << std::fixed << std::setprecision(2) << path[i].getXPosition();
        yStream << std::fixed << std::setprecision(2) << path[i].getYPosition();

        instruction = "Go to product " + path[i].getProductID() + " at (" +
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

/**
 * @brief	Return current position of the user. (Unused currently)
 *
 * @return  Tuple of coordinates
 */

std::tuple<float,float> PathFinder::getCurrentPosition(void) {
    return currentPosition;
}

/**
 * @brief	Set current position of the user. (Unused currently)
 *
 * @params  pos Tuple of coordinates
 */

void PathFinder::setCurrentPosition(std::tuple<float,float>& pos) {
    currentPosition = pos;
}

/**
 * @brief   returns the general direction of 2 points.
 * 
 * @param   p1     tuple of coordinates
 * @param   p2     tuple of coordinates
 * @return  enum direction, info can be found in the
 *                      header file
 */
Compass PathFinder::getHeading(std::tuple<float, float, std::string> p1,
    std::tuple<float, float, std::string> p2)
{
    // to get direction headed, do p2.x - p1.x and
    // p2.y-p1.y
    
    float x = std::get<0>(p2) - std::get<0>(p1);
    float y = std::get<1>(p2) - std::get<1>(p1);
    // North is when x = 0, and y is negative
    if (x == 0.0 && y < 0.0) {
        return Compass::North;
    }// NorthEast is when x is positive and y is negative
    else if (x > 0.0 && y < 0.0) {
        return Compass::NorthEast;
    }// East is when x is positive and y = 0
    else if (x > 0.0 && y == 0.0) {
        return Compass::East;
    }// SouthEast is when x is positive and y is positive 
    else if (x > 0.0 && y > 0.0) {
        return Compass::SouthEast;
    }// South is when x is 0 and y is positive
    else if (x == 0.0 && y > 0.0) {
        return Compass::South;
    }// SouthWest is when x is negative and y is positive
    else if (x < 0.0 && y > 0.0) {
        return Compass::SouthWest;
    }// West is when x is negative and y is 0
    else if (x < 0.0 && y == 0.0) {
        return Compass::West;
    }// NorthWest is when x is negative and y is positive
    else if (x < 0.0 && y < 0.0) {
        return Compass::NorthWest;
    }// else dont move
    else {
        return Compass::Stay;
    }
}
