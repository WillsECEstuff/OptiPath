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

#include <tuple>
#include <string>
#include "third_party/nlohmann/single_include/nlohmann/json.hpp"

class Product
{
private:
	std::string productID;
	float xPosition;
	float yPosition;

	

public:
	Product(std::string pID, std::tuple<float, float> t);
	Product(std::string pID, float x, float y);

	std::tuple<float, float> getPositionTuple(void);
	float getXPosition(void);
	float getYPosition(void);
	std::string getProductID(void);

};


