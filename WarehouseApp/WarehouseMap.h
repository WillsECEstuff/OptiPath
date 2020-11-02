#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "third_party/nlohmann/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class WarehouseMap
{

private:
	json shelves;
	json WarehouseDimensions;
	json aisles;
	static WarehouseMap* instance;
	WarehouseMap() {};

	void findShelveEnds(void);
public:
	static WarehouseMap* getInstance(void);
	void buildWarehouseMap(json productDatabase);
	json getShelves(void);
	json getSingleShelf(std::string shelf);
};




/*
json structure for shelves

{
	"shelve_row_number(string)":
		{
			"occupied"	:	std::set<int>;
			"start"		:	int;
			"end"		:	int;
		}
}
*/
