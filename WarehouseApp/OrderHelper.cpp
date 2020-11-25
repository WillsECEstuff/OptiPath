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
    std::cout << "productList size: " << productList.size() << std::endl;
    std::cout << "product ID: " << productList[0] << std::endl;
    for (std::vector<std::string>::iterator it = productList.begin(); it != productList.end(); ++it) {
        //std::cout << "product ID: " << *it << std::endl;
		t = d->getProductPosition(*it);

        std::cout << "product location: " << std::get<0>(t) << "," << std::get<1>(t) << std::endl;

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


/**
 * @brief	Create orders from a given file. Orders are expected to be 
 *			separated by a new line, and products are expected to be
 *			separated by commas. This function will return a vector of 
 *			orders, starting with a supplied orderID. orderID will be 
 *			incremented by 1 per new order.
 * 
 * @param	filePath	string,	a valid filepath
 * @param	orderID		int,	starting orderID given to the orders
 * @param	priority	int,	priority of order. default is 1
 * @return	vector of Order objects
 */
std::vector<Order> createOrdersfromFile(std::string filePath, int orderID, int priority)
{
	int oID = orderID;
	std::string line;
	std::ifstream infile(filePath);
	std::vector<Order> o;

	// goes through all the lines in the file
	while (std::getline(infile, line)) {
		o.push_back(createOrderfromString(line, oID++, priority));
	}
	
	return o;
}

/**
 * @brief	Creates an order from a string. The string is expected
 *			to have product IDs separated by a comma.
 * 
 * @param	products		string containing product IDs separated
 *							by a comma
 * @param	orderID			int,	orderID
 * @param	priority		int,	priority of order. default is 1
 * @return	Order
 */
Order createOrderfromString(std::string products, int orderID, int priority)
{
	std::istringstream iss(products);
	std::vector<std::string> tokens;

	// tokenizes the line with the comma as a delimiter
    for (std::string each; std::getline(iss, each, ',');) {
		// remove white space
		tokens.push_back(trim(each));
	}
    return createOrderfromVector(tokens, orderID, priority);
}


/**
 * @brief	Removes white space in front and at the end of the string.
 *			
 * 
 * @param	line,		string
 * @return	string
 */
std::string trim(const std::string& line) {
    const char* WhiteSpace = " \t\v\r\n";

	const auto strBegin = line.find_first_not_of(WhiteSpace);
	if (strBegin == std::string::npos) {
		return ""; // empty string
	}
	const auto strEnd = line.find_last_not_of(WhiteSpace);
	const auto strRange = strEnd - strBegin + 1;
    
    return line.substr(strBegin, strRange);
}
