/*****************************************************************//**
 * @file   Ticket.h
 * @brief  The ticket class is what the warehouse gets. This class is
 *			mainly a fill in. However, this ticket class contains the
 *			expected data structure the warehouse application will use
 *			to create an order class. 
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/
#pragma once

#include <list>

class Ticket
{
private:
	std::list<int> pIDList;
	int priority;

public:
	Ticket(int p = 1);

	void addProductIDtoList(int productID);

	std::list<int> getProductList(void);

	int getPriority(void);
};


