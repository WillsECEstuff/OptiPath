/*****************************************************************//**
 * @file   WarehouseMap.cpp
 * @brief  This file contains the definitions for WarehouseMap.h.
 * 
 * @author Tony
 * @date   November 2020
 *********************************************************************/
#include "WarehouseMap.h"

WarehouseMap* WarehouseMap::instance = NULL;

/**
 * @brief	This function allows only one intance of the WarehouseMap.
 *			If there are no instances of the WarehouseMap, create the
 *			object and return it. Otherwise, return the existing object.
 * 
 * @return	instance	return the instance of the WarehouseMap
 */
WarehouseMap* WarehouseMap::getInstance(void)
{
	if (instance == NULL) {
		instance = new WarehouseMap;
	}
	return instance;
}


/**
 * @brief	This function construct the shelves JSON data from the
 *			product Database from Database.h/cpp. It builds JSON
 *			members shelves and WarehouseDimension. The JSON
 *			data structure for both "shelves" and "WarehouseDimension"
 *			can be seen in WarehouseMap.h
 * 
 * @param	productDatabase		JSON from returnDatabase in 
 *								Database.h
 */
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

/**
 * @brief	Returns the shelves JSON structure. The structure
 *			of shelves can be seen in WarehouseMap.h.
 * 
 * @return	json
 */
json WarehouseMap::getShelves(void)
{
	return shelves;
}


/**
 * @brief	This function returns the nested JSON object
 *			within the shelves JSON structure. This JSON
 *			includes keys such as "occupied", "start", and
 *			end. If no shelf exist, return a NULL pointer.
 * 
 * @param	shelf		shelf row number in string format
 * @return	JSON
 */
json WarehouseMap::getSingleShelf(std::string shelf)
{
	json::iterator it = shelves.find(shelf);
	if (it == shelves.end()) {
		// return NULL if not exist
		return NULL;
	}
	else {
		return it.value();
	}
}

/**
 * @brief	This is a private function whose job is to find
 *			where a shelf start within a row and end.
 *			The JSON key for where a shelf starts is "begin"
 *			and where a shelf stops is "end". The integer
 *			where the shelf begins and ends means that
 *			space is occupied by a shelf.
 * 
 */
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


