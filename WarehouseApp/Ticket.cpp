/*****************************************************************//**
 * @file   Ticket.cpp
 * @brief  This source file contains the definition for Ticket.h
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/

#include "Ticket.h"

/**
 * Unused at the moment due to changes in scope.
 */


/**
 * @brief	This is a constructor function. The function clear the
 *			product ID list and sets the priority
 * 
 * @param	p		p takes an integer between 1 and 100 inclusive
 *					If p is < 1, p is set to 1. If p is > 100, p is 
 *					set to 100. 
 */
Ticket::Ticket(int p) {
	pIDList.clear();
	if (p < 1) {
		priority = 1;
	}
	else if (p > 100) {
		priority = 100;
	}
	else {
		priority = p;
	}
}

/**
 * @brief	Adds a product ID to the end of the pIDList
 * 
 * @param	productID	productID is an int
 */
void Ticket::addProductIDtoList(int productID) {
	pIDList.push_back(productID);
}

/**
 * @brief	returns the pIDList.
 * 
 * @return	returns the pIDList in form of std::list<int>
 */
std::list<int> Ticket::getProductList(void) {
	return pIDList;
}

/**
 * @brief	gets the priority of the ticket.
 * 
 * @return	return an int which indicates the priority of the ticket.
 */
int Ticket::getPriority(void) {
	return priority;
}