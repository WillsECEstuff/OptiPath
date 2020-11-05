#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "Database.h"
#include "Order.h"
#include "Product.h"


Order createOrderfromVector(Database* d, std::vector<std::string> productList,
	int oID = 1, int priority = 1);

Order createOrderfromProductID(Database* d, std::string pID,
	int oID = 1, int priority = 1);