/*****************************************************************//**
 * @file   Product.cpp
 * @brief  This source file is the definitions for Product.h
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/

#include "Product.h"

/**
 * @brief	This is one of the constructors for the Product class
 *			This constructer expects a productID, pID, and a 
 *			tuple<float, float> in the xy coordinate system to
 *			indicate its position in the warehouse
 * 
 * @param	pID		pID is an integer that will indicate the 
 *					productID
 * @param	t		t is a tuple<float, float> that indicates
 *					the product's position. The tuple expects
 *					the xy coordinate system
 */
Product::Product(std::string pID, std::tuple<float, float> t) {
	productID = pID;
	xPosition = std::get<0>(t);
	yPosition = std::get<1>(t);
}

/**
 * @brief	This is one of the constructors for the Product class
 *			This construct expects a productID, pID, and two floats, 
 *			x and y, to indicate its position in the warehouse
 * 
 * @param	pID		pID is an integer that will indicate the 
 *					productID
 * @param	x		x is a float that indicates the product's x
 *					position in a warehouse
 * @param	y		y is a float that indicates the product's y
 *					position in a warehouse
 */
Product::Product(std::string pID, float x, float y) {
	productID = pID;
	xPosition = x;
	yPosition = y;
}

/**
 * @brief	This function returns the position of a product in
 *			a tuple<float, float>. The tuple represents the position
 *			by the xy coordinate system.
 * 
 * @return	tuple<float, float> in the xy coordinate system
 */
std::tuple<float, float> Product::getPositionTuple(void) {
	return std::make_tuple(xPosition, yPosition);
}

/**
 * @brief	This function returns the x position of a product
 *			 in the cartesian coordinate system
 * 
 * @return	returns a float
 */
float Product::getXPosition(void) {
	return xPosition;
}

/**
 * @brief	This function returns the y position of a product
 *			in the cartesian coordinate system
 *
 * @return	returns a float
 */
float Product::getYPosition(void) {
	return yPosition;
}

/**
 * @brief	This function returns the product ID of a product
 *
 * @return	returns a string
 */
std::string Product::getProductID(void) {
	return productID;
}

