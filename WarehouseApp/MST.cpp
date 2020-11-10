/*****************************************************************//**
 * @file   MST.cpp
 * @brief  This source file contains the definitions for MST.h
 * 
 * @author Tony
 * @date   November 2020
 *********************************************************************/
#include "MST.h"

/**
 * @brief	This function is a constructor for MST. It builds the
 *			adjacency matrix and the productList + start location.
 * 
 * @param	o				Order object with Products inside
 * @param	startLocation	Product class only containing
 *							the location
 */
MST::MST(Order o, Product startLocation)
{
	buildAdjMatrix(o, startLocation);
}

/**
 * @brief	This function is a private function used in the constructor.
 *			This function builds the adjacency matrix and the vertices,
 *			which is the Products and start location, with start location
 *			at position 0.
 * 
 * @param	o				Order object with Products inside
 * @param	startLocation	Product class only containing
 *							the location
 */
void MST::buildAdjMatrix(Order o, Product startLocation)
{
	clearAdjMatrix();
	vertices = o.getProductList();
	vertices.push_front(startLocation);
	vertexSize = (int) vertices.size();
	for (int i = 0; i < vertexSize; i++) {
		AdjMatrix.push_back(std::vector<float>(vertexSize, -1.0));
	}

	int i1 = 0;
	for (auto const& it1 : vertices) {

		int j1 = 0;
		for (auto const& it2 : vertices) {
			double d = distanceBetweenProductsEuclidean(it1, it2);
			AdjMatrix[i1][j1] = (float) d;
			j1 += 1;
		}
		i1++;
	}
}

/**
 * @brief	Clears the Adjacency matrix. Makes sure there is nothing
 *			inside it.
 * 
 */
void MST::clearAdjMatrix(void)
{
	AdjMatrix.clear();
}

/**
 * @brief	Clears the verticies list. Makes sure there is nothing
 *			inside it.
 * 
 */
void MST::clearVertices(void)
{
	vertices.clear();
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
double MST::distanceBetweenProductsEuclidean(Product product1, Product product2)
{
	double distance = sqrt(pow(product1.getXPosition() - product2.getXPosition(), 2) +
		pow(product1.getYPosition() - product2.getYPosition(), 2));
	//std::cout<<"Distance between "<<product1.getProductID()<<" and "<<product2.getProductID()<<" = "<<distance<<std::endl;
	return distance;
}

/**
 * @brief	Returns a boolean if the edge is valid or not.
 *			Scenarios in which the function returns 
 *			false:
 *				If it is the same vertices (i==j),
 *				If both vertices have not been visited,
 *				If both vertices have been visited.
 *			Return true otherwise.
 *				
 * 
 * @param	i		int,	indicates index for AdjMatrix
 * @param	j		int,	indicates index for AdjMatrix
 * @param	inMST	vector<bools>,	indicates if a vertex
 *						has been visited
 * @return	bool
 */
bool MST::isValidEdge(int i, int j, std::vector<bool> inMST)
{
	if (i == j) {
		return false;
	}
	if (inMST[i] == false && inMST[j] == false) {
		return false;
	}
	else if (inMST[i] == true && inMST[j] == true) {
		return false;
	}
	return true;
}

/**
 * @brief	This function implements Prim's algorithm to find 
 *			the minumum cost. This algorithm does not take into
 *			account any backtracking a user may do, returning to
 *			the end location, or extra disctance due to shelves.
 *			This algorithm is only for finding the ideal lower bound.
 * 
 * @return	float
 */
float MST::findLowerBound(void)
{
	std::vector<bool> inMST(vertexSize, false);

	// include first vertex in MST
	inMST[0] = true;

	// keep adding edges while number of included edges does not
	// become V-1
	int edge_count = 0;
	double mincost = 0.0;
	while (edge_count < vertexSize - 1) {

		// Find minimum weight valid edge
		double min = (double)INT_MAX;
		int a = -1, b = -1;
		for (int i = 0; i < vertexSize; i++) {
			for (int j = 0; j < vertexSize; j++) {
				if (AdjMatrix[i][j] < min) {
					if (isValidEdge(i, j, inMST)) {
						min = AdjMatrix[i][j];
						a = i;
						b = j;
					}
					
				}
			}
		}
		if (a != -1 && b != -1) {
			edge_count++;
			mincost = mincost + min;
			inMST[b] = inMST[a] = true;
		}

	}
	return (float) mincost;
}

/**
 * @brief	This function prints the Adjacency Matrix.
 * 
 */
void MST::printAdjacencyMatrix(void)
{
	for (int i = 0; i < AdjMatrix.size(); i++) {
		for (int j = 0; j < AdjMatrix[i].size(); j++) {
			std::cout << AdjMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
