// WarehouseDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This file is a small driver to get this classes and objects to run together
//

#include <iostream>
#include <list>
#include <tuple>

#include "Database.h"
#include "Ticket.h"
#include "Order.h"

int main(int argc, char** argv)
{
    std::cout << "Hello World!\n" << std::endl;;
    // Instantiate a database
    // only expected 1 instance
    Database* d = d->getInstance();

    // Instantiate an order
    // can have multiple orders
    Order o(1,1);

    // make sure database is clear before reading and populating
    // database from the text file
    d->deleteDatabase();
    d->populateDatabase("qvBox-warehouse-data-f20-v01.txt");

    // using the database, get product position
    // in this example, I am getting a tuple
    std::tuple<float, float> t = d->getProductPosition("1");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;

    // create a product class
    // and add the product into the order
    Product p("1", t);
    o.addProduct(p);

    t = d->getProductPosition("45");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;

    p.~Product();
    new(&p) Product("45", t);
    o.addProduct(p);

    t = d->getProductPosition("102");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;

    p.~Product();
    new(&p) Product("102", t);
    o.addProduct(p);

    t = d->getProductPosition("16");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;

    p.~Product();
    new(&p) Product("16", t);
    o.addProduct(p);

    // iterates through the product list
    // and check the productID and positions of each product
    std::list<Product> l = o.getProductList();
    for (auto& it:l) {
        std::cout << "ID: " << it.getProductID() << "\txPosition: " << it.getXPosition()
            << "\tyPosition: " << it.getYPosition() << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
