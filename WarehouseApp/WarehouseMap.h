/*****************************************************************//**
 * @file   WarehouseMap.h
 * @brief  This header includes the WarehouseMap class. It implements
 *			a singleton in which only one instance can be made at a 
 *			time. This class function is to provide the dimensions
 *			of the warehouse as well as deducing the location of the
 *			shelves. 
 * 
 * @author Tony
 * @date   November 2020
 *********************************************************************/

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
	json shelves;	/* A JSON object structure can be seen below */
	json WarehouseDimensions; /* A JSON object structure can be seen below */
	json aisles; /* currently unused */
    std::vector<std::tuple<std::string, int, int>> shelfSpecs; // for retrieving shelf specs
	static WarehouseMap* instance;
	/* Private constructor so that no objects can be created explicitly */
	WarehouseMap() {};

	void findShelveEnds(void);
public:
	static WarehouseMap* getInstance(void);
	void buildWarehouseMap(json productDatabase);
	json getShelves(void);
    json getSingleShelf(std::string shelf);
    std::vector<std::tuple<int, int, int>> getShelfSpecs(void);
};


/*
json structure for shelves

{
	"shelve_row_number(string)":
		{
			"occupied"	:	std::set<int>,
			"start"		:	int,
			"end"		:	int
		}
	...
	...
}
*/

/*
json structure for WarehouseDimensions
{
	"x"	:	int,
	"y"	:	int
}
*/

/*
tuple structure and meaning for getShelfSpecs
<int, int, int>
<shelf#, start, end>
*/
