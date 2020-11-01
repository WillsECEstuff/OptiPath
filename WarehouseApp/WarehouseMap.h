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
public:
	static WarehouseMap* getInstance(void);
	void buildWarehouseMap(json productDatabase);
};

