/*****************************************************************//**
 * @file   Order.h
 * @brief  This header includes the Order class. The order class 
 *			contains members: priority, orderID, and productList.
 *			The priority is an integer which dictate its position
 *			in a priority queue. The orderID is to differientiate it
 *			from other orders, productList is to keep multiple orders.
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/

#pragma once

#include<algorithm>
#include <list>
#include "Product.h"


class Order
{
private:
	int priority;
	int orderID;

	std::list<Product> productList;

	

public:
	Order(int oID, int p = 1);

	void addProduct(Product p);

	std::list<Product> getProductList(void);

	void changePriority(int p);

	int getPriority(void);

};




