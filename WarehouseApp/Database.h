/*****************************************************************//**
 * @file   Database.h
 * @brief  This header includes the Database class. It implements a 
 *			singleton and will only have 1 instance at a time. This
 *			class is a simple database whose job is to read from a 
 *			text file and store its content in a map. The database
 *			can be called to get information about products.
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/


#pragma once

#include <iostream>
#include <tuple>
#include <string>
#include <map>
#include <fstream>
#include "third_party/nlohmann/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class Database {
private:
	static Database* instance;
	//std::map<int, std::tuple<float, float>> database;
	json database;
	/* Private constructor so that no objects can be created */
    Database() {};

public:
	static Database* getInstance(void);

	void deleteDatabase(void);

	void populateDatabase(std::string filename);

	std::tuple<float, float> getProductPosition(std::string productID);
    std::vector<std::tuple<float, float>> getLocList();
};
