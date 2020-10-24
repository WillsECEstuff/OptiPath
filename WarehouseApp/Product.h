/*****************************************************************//**
 * @file   Product.h
 * @brief  This header includes the class for Products. The product
 *			class includes members such as productID, for 
 *			differientation between other product IDs, xPosition,
 *			and yPosition for the product's position in the warehouse.
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/

#pragma once

#include<tuple>

class Product
{
private:
	int productID;
	float xPosition;
	float yPosition;

	

public:
	Product(int pID, std::tuple<float, float> t);
	Product(int pID, float x, float y);

	std::tuple<float, float> getPositionTuple(void);
	float getXPosition(void);
	float getYPosition(void);
	int getProductID(void);

};


