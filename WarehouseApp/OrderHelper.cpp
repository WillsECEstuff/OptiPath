/*****************************************************************//**
 * @file   OrderHelper.cpp
 * @brief  This file is contains the definitions for OrderHelper.h
 * 
 * @author Tony
 * @date   November 2020
 *********************************************************************/


#include "OrderHelper.h"

/**
 * @brief	Creates and returns an Order object. This functions takes
 *			a vector of productIDs in string form, finds the location
 *			in the database, and creates an order out of them. If 
 *			a product does not exist within a database, it is ignored.
 *			oID and priority are both default 1.
 * 
 * @param	productList		a vector of strings containing product IDs
 * @param	oID				int, should be a non negative number
 * @param	priority		int, should be integer from 1-100
 * @return	Order 
 */
Order createOrderfromVector(std::vector<std::string> productList,
	int oID, int priority)
{
	
	Database* d = d->getInstance();
	
	Order o(oID, priority);
	std::tuple<float, float> t;

	for (std::vector<std::string>::iterator it = productList.begin(); it != productList.end(); ++it) {
		t = d->getProductPosition(*it);

		// skip if the tuple x or y value is less than 0
		if (!(std::get<0>(t) < 0 || std::get<1>(t) < 0)) {
			Product p(*it, t);
			o.addProduct(p);
		}

	}

	return o;
}

/**
 * @brief	Creates and returns an Order object. This functions takes
 *			a productID a in string form, finds the location
 *			in the database, and creates an order out of it. If 
 *			a product does not exist within a database, the function will
 *			throw a logic_error so the information can be relayed by the
 *			GUI.
 * 
 * @param	pID			string, productID in string form
 * @param	oID			int, should be a non negative number
 * @param	priority	int, should be integer from 1-100
 * @return	Order
 */
Order createOrderfromProductID(std::string pID, int oID, int priority)
{
	Database* d = d->getInstance();
	Order o(oID, priority);
	std::tuple<float, float> t;

	
	t = d->getProductPosition(pID);

	// skip if the tuple x or y value is less than 0
	if (!(std::get<0>(t) < 0 || std::get<1>(t) < 0)) {
		Product p(pID, t);
		o.addProduct(p);
	}
	else {
		throw std::logic_error("Product does not exist within the database.");
	}

	return o;
}

/**
 * @brief	This function adds products to an existing order.
 *			This function takes a vector of productIDs in string form,
 *			finds the location in the database, and adds it to the 
 *			order. ProductIDs not in the database are ignored.
 * 
 * @param	productList		a vector of strings containing product IDs
 * @param	o				Order to be added
 */
void addVectortoExistingOrder(std::vector<std::string> productList,
	Order* o) 
{
	
	if (o == NULL) {
		return;
	}
	Database* d = d->getInstance();

	std::tuple<float, float> t;
	for (std::vector<std::string>::iterator it = productList.begin(); it != productList.end(); ++it) {
		t = d->getProductPosition(*it);

		// skip if the tuple x or y value is less than 0
		if (!(std::get<0>(t) < 0 || std::get<1>(t) < 0)) {
			Product p(*it, t);
			o->addProduct(p);
		}

	}

}

/**
 * @brief	This function adds a single product to an existing order.
 *			This function takes a productID in string form,
 *			finds the location in the database, and adds it to the
 *			order. ProductIDs not in the database are ignored. If 
 *			a product does not exist within a database, the function will
 *			throw a logic_error so the information can be relayed by the
 *			GUI.
 *
 * @param	pID				string, productID in string form
 * @param	o				Order to be added
 */
void addProducttoExistingOrder(std::string pID, Order* o) 
{

	if (o == NULL) {
		return;
	}
	Database* d = d->getInstance();

	std::tuple<float, float> t;

	t = d->getProductPosition(pID);

	// skip if the tuple x or y value is less than 0
	if (!(std::get<0>(t) < 0 || std::get<1>(t) < 0)) {
		Product p(pID, t);
		o->addProduct(p);
	}
	else {
		throw std::logic_error("Product does not exist within the database.");
	}

}