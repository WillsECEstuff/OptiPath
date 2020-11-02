#include "WarehouseMap.h"

WarehouseMap* WarehouseMap::instance = NULL;

WarehouseMap* WarehouseMap::getInstance(void)
{
	if (instance == NULL) {
		instance = new WarehouseMap;
	}
	return instance;
}

void WarehouseMap::buildWarehouseMap(json productDatabase)
{
	int xDimension = 0;
	int yDimension = 0;
	std::tuple<float, float> t;

	// populate rows within the warehouse and max dimensions
	for (auto it : productDatabase.items()) {
		//std::cout << it.key() << " : " << it.value() << std::endl;
		t = it.value();
		int row = (int)std::get<1>(t);
		int col = (int)std::get<0>(t);
		std::string s_row =std::to_string(row);

		if (col > yDimension) {
			yDimension = col;
		}
		if (row > xDimension) {
			xDimension = row;
		}

		// if row does not exist, create row in json
		// if row exist, add x position (floor) to the vector
		if (shelves.contains(s_row)) {
			std::set<int> set = shelves[s_row]["occupied"];
			set.insert(col);
			shelves[s_row]["occupied"] = set;
		}
		else { // else no key at row exist
			json newObj;
			std::set<int> set;
			set.insert(col);
			newObj["occupied"] = set;
			shelves[s_row] = newObj;
		}
	}
	

	// add 1 to xDimension and yDimension for final warehouse size
	WarehouseDimensions["x"] = ++xDimension;
	WarehouseDimensions["y"] = ++yDimension;

	findShelveEnds();

	//print json with pretty printing
	std::cout << shelves.dump(4) << std::endl;
}

json WarehouseMap::getShelves(void)
{
	return shelves;
}

json WarehouseMap::getSingleShelf(std::string shelf)
{
	json::iterator it = shelves.find(shelf);
	if (it == shelves.end()) {
		// return -1,-1 if not exist
		return NULL;
	}
	else {
		return it.value();
	}
}


void WarehouseMap::findShelveEnds(void) {

	for (auto it : shelves.items()) {
		json j = it.value();
		//std::cout <<j.dump(4) << std::endl;

		std::set<int> set = j["occupied"];
		std::set<int>::iterator sit;
		std::set<int>::reverse_iterator rsit;
		sit = set.begin();
		int begin = *sit;
		rsit = set.rbegin();
		int end = *rsit;

		it.value()["begin"] = begin;
		it.value()["end"] = end;

	}
}

json 

