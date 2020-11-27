/*****************************************************************//**
 * @file   Order.cpp
 * @brief  This source file contains the definitions for Order.h
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/

#include "Order.h"

 /**
  * @brief	This is a constructor for the Order object. 
  *			Default values will be set 1.
  */
Order::Order(void)
{
    priority = 1;
    orderID = 1;
}

/**
 * @brief	This is a constructor for the Order object. This constructor
 *			requires 2 arguments
 * 
 * @param	oID		oID is the assigned orderID. oID should not be a 
 *					negative number
 * @param	p		p is the assigned priority. p's default is 1. p
 *					should be a value between 1 and 100 inclusive
 */
Order::Order(int oID, int p) {
	orderID = oID;
	if (p < 1) {
		priority = 1;
	}
	else if (p > 100) {
		priority = 100;
	}
	else {
		priority = p;
	}

	productList.clear();

	status = ORDER_PENDING;
}

/**
 * @brief	This is a constructor for the Order object. This constructor
 *			requires 3 arguments
 *
 * @param	oID		oID is the assigned orderID. oID should not be a
 *					negative number
 * @param	p		p is the assigned priority. p's default is 1. p
 *					should be a value between 1 and 100 inclusive
 *
 * @param   stat    Status enum object
 *                  ORDER_PENDING - 0
                    ORDER_EXECUTED - 1
 */
Order::Order(int oID,int p, Status stat) {
    orderID = oID;
    if (p < 1) {
        priority = 1;
    }
    else if (p > 100) {
        priority = 100;
    }
    else {
        priority = p;
    }
    status = stat;
    productList.clear();
}


/**
 * @brief	This function adds an already constructed Product object
 *			to the productList of an Order object. If the product's 
 *			position is not valid, ignore the order
 * 
 * @param	p		p is a Product object. It is expected for the 
 *					object to have valid position variables.
 */
void Order::addProduct(Product p) {
	if (p.getXPosition() == -1 || p.getYPosition() == -1) {
		return;
	}
	productList.push_back(p);
}

/**
 * @brief	Returns the Order object's productList.
 * 
 * @return	Returns the Order object's productList.
 */
std::list<Product> Order::getProductList(void) {
	return productList;
}

/**
 * @brief	This function changes the priority of an order.
 *			Unlike the constructor, this function accepts values
 *			greater than 100. However, values less than 1 are not
 *			accepted and will set the priority to 1.
 * 
 * @param	p		p is an integer > 1.
 */
void Order::changePriority(int p) {
	if (p < 1) {
		priority = 1;
	}
	else {
		priority = p;
	}
	
}

/**
 * @brief	Get the Order object's priority.
 * 
 * @return	returns an integer indicating the object's priority.
 */
int Order::getPriority(void) {
	return priority;
}

/**
 * @brief	Get the Order size.
 *
 * @return	returns an integer indicating the object's size.
 */
size_t Order::getSize(void) {
    return productList.size();
}

/**
 * @brief	Get the Order size.
 *
 * @return	returns an integer indicating the object's size.
 */

int Order::getOrderID(void) {
    return orderID;
}

/**
 * @brief	Set the Order status to ORDER_EXECUTED.
 */
void Order::orderCompleted() {
    status = ORDER_EXECUTED;
}

/**
 * @brief	Set the Order status to ORDER_PENDING.
 */
void Order::orderPending() {
    status = ORDER_PENDING;
}

/**
 * @brief	Get the Order status.
 *
 * @return	returns an enum Object of type Status
 */
Order::Status Order::getOrderStatus() {
    return status;
}

