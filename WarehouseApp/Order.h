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

#include <algorithm>
#include <list>
#include "Product.h"


class Order
{
public:
    enum Status {
        ORDER_PENDING,
        ORDER_EXECUTED
    };

    Order(void);
    Order(int oID, int p = 1);
    Order(int oID, int p, Status stat);

	void addProduct(Product p);
	std::list<Product> getProductList(void);
    void orderCompleted();
    void orderPending();
    Status getOrderStatus();
	void changePriority(int p);
    size_t getSize(void);
	int getPriority(void);
    int getOrderID(void);

private:
    int priority;
    int orderID;

    Order::Status status;
    std::list<Product> productList;
};



