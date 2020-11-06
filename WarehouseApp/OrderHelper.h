/*****************************************************************//**
 * @file   OrderHelper.h
 * @brief  This is the header file for helper functions regarding 
 *			Orders. The main functionality is creating an order
 *			based off a vector of strings or single string, or 
 *			adding products to an order by a vector of strings
 *			or a string.
 *			
 * 
 * @author Tony
 * @date   November 2020
 *********************************************************************/

#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "Database.h"
#include "Order.h"
#include "Product.h"


Order createOrderfromVector(std::vector<std::string> productList,
	int oID = 1, int priority = 1);

Order createOrderfromProductID(std::string pID, int oID = 1, int priority = 1);

void addVectortoExistingOrder(std::vector<std::string> productList,
	Order* o);

void addProducttoExistingOrder(std::string pID, Order* o);