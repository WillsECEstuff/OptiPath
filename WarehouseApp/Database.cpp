/*****************************************************************//**
 * @file   Database.cpp
 * @brief  This file contains the definitions for Database.h.
 * 
 * @author Tony
 * @date   October 2020
 *********************************************************************/

#include "Database.h"

Database* Database::instance = NULL;

/**
 * @brief	This function allows only one intance of the database.
 *			If there are no instances of the database, create the
 *			database and return it. Otherwise, return the database.
 * 
 * @return	instance	return the instance of the database
 */
Database* Database::getInstance(void) {
	if (instance == NULL) {
		instance = new Database;
	}
	return instance;
}

/**
 * @brief	Deletes all items within the map data structure.
 * 
 */
void Database::deleteDatabase(void) {
	database.clear();
}

/**
 * @brief	Populates the database from a provided text file. The database
 *			will convert text into a JSON object in which the product ID will
 *			be a key and the position are the values.
 *
 * @param	filename	The filename which we are reading the
 *						database values from.
 */
void Database::populateDatabase(std::string filename) {
	std::string s1, s2, s3;
	std::string productID;
	float x, y;

	std::cout << "Opening file called " << filename << std::endl;

	std::ifstream infile(filename);

	if (!(infile >> s1 >> s2 >> s3)) {
		/* error, could not read first line!*/
		std::cout << "ERROR: Unable to read first line." << std::endl;
		std::string errorMSG = "Error opening " + filename + ". Please check file.";
		throw std::runtime_error(errorMSG);
	}

	if (s1 != "ProductID" || s2 != "xLocation" || s3 != "yLocation") {

		std::cout << "ERROR: File format not expected." << std::endl;
		std::string errorMSG = "Formatting error in " + filename + ". Please check file.";
		throw std::runtime_error(errorMSG);
	}

	while (infile >> productID >> x >> y) {
		//std::cout << productID << " " << x << " " << y << std::endl;
		//database.emplace(productID, std::make_tuple(x, y));
		database[productID] = {x, y};
	}

	std::cout << "Finished creating Database " << std::endl;
}

/**
 * @brief	This function returns a tuple<float, float> in the 
 *			xy coordinate format given a particular productID. Before
 *			using this function, the database should be populated by using
 *			the populateDatabase function.
 * 
 * @param	productID	This value is a unique integer value indicating
 *						a product.
 * @return	This function returns a tuple<float, float> in the 
 *			xy coordinate. If a product does not exist in the database,
 *			the function will return a tuple of <-1, -1>.
 */
std::tuple<float, float> Database::getProductPosition(std::string productID) {
	//std::map<int, std::tuple<float, float>>::iterator it;
	json::iterator it = database.find(productID);

	if (it == database.end()) {
		// return -1,-1 if not exist
		return std::make_tuple((float)-1, (float)-1);
	}
	else {
		return std::make_tuple((*it)[0],(*it)[1]);
	}
}

/**
 * @brief This function returns a vector of tuples<float, float> in the cartesian 
 *		  coordinate format. The vector contains all the locations of products 
 *		  in the database.
 * 
 * @return 
 */
std::vector<std::tuple<float, float>> Database::getLocList() {
    std::vector<std::tuple<float, float>> locList;

    for (json::iterator it = database.begin(); it != database.end(); it++) {
        std::tuple<float, float> temp = std::make_tuple((*it)[0], (*it)[1]);
        locList.push_back(temp);
    }

    return locList;
}

/**
 * @brief	This function returns the whole JSON database from
 *			the database class.
 * 
 * @return	JSON
 */
json Database::returnDatabase(void)
{
	return database;
}

/**
 * @brief	returns a boolean if the database is empty or not
 *			i.e. returns true if no key/value pair is in JSON
 * 
 * @return	boolean
 */
bool Database::isDatabaseEmpty(void) {
	return database.empty();
}