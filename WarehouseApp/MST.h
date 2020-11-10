/*****************************************************************//**
 * @file   MST.h
 * @brief  This class provides an ideal lower bound to our routing
 *			algorithm. The lower bound in in this MST does not 
 *			incorporate the ending location (assumes start is end).
 *			This MST also does not include the distance around shelves.
 *			This is an unrealistic lower bound.
 * 
 * @author Tony
 * @date   November 2020
 *********************************************************************/
#pragma once

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include "Order.h"

class MST
{
private:
	std::vector<std::vector<float>> AdjMatrix;	// adjacency matrix
	std::list<Product> vertices;				// list of vertices (start @ 0 and products)
	int vertexSize;								// vertices.size()

	void buildAdjMatrix(Order o, Product startLocation);
	void clearAdjMatrix(void);
	void clearVertices(void);
	double distanceBetweenProductsEuclidean(Product product1, Product product2);
	bool isValidEdge(int i, int j, std::vector<bool> inMST);

public:
	MST(Order o, Product startLocation);
	float findLowerBound(void);
	void printAdjacencyMatrix(void);

};

