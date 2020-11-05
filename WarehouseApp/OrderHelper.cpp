


#include "OrderHelper.h"


Order createOrderfromVector(Database* d, std::vector<std::string> productList,
	int oID, int priority)
{
	if (d == NULL) {
		d = d->getInstance();
	}
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

Order createOrderfromProductID(Database* d, std::string pID,
	int oID, int priority)
{
	if (d == NULL) {
		d = d->getInstance();
	}
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

void addVectortoExistingOrder(Database* d, std::vector<std::string> productList,
	Order* o) 
{
	
	if (o == NULL) {
		return;
	}
	if (d == NULL) {
		d = d->getInstance();
	}

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

void addProducttoExistingOrder(Database* d, std::string pID, Order* o) 
{

	if (o == NULL) {
		return;
	}
	if (d == NULL) {
		d = d->getInstance();
	}

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