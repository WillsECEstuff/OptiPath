// WarehouseDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This file is a small driver to get this classes and objects to run together
//

#include <iostream>
#include <list>
#include <tuple>
#include <QApplication>
#include <QPointF>
#include <QVector>

#include "Database.h"
#include "Ticket.h"
#include "Order.h"
#include "PathFinder.h"
#include "mainwindow.h"
#include "Inventory.h"
#include "WarehouseMap.h"
#include <QDir>
#include <QDebug>


Order createOrders(Database* d, Order o);


int main(int argc, char** argv)
{
    const float TILE_SIZE = 30;
    const float SCALE = 5;

    qDebug() << QDir().currentPath(); // verify that the warehouse .txt file is in the path!
    QApplication a(argc, argv);

    // Instantiate a database
    // only expected 1 instance
    Database* d = d->getInstance();

    //Instantiate a warehouse map
    // only expected 1 instance
    WarehouseMap* Map = Map->getInstance();

    // Instantiate an order
    // can have multiple orders
    Order o(1,1);

    // Instantiate an adjacency matrix
    AdjacencyMatrix matrix;

    // Instantiate path finder
    PathFinder pathFinder;

    // Instantiate vector of all product points and all points
    QVector<QPointF> pLocs;
    QVector<QPointF> aLocs;

    // make sure database is clear before reading and populating
    // database from the text file
    d->deleteDatabase();
    d->populateDatabase("qvBox-warehouse-data-f20-v01.txt");


    // creating a Warehouse Map
    Map->buildWarehouseMap(d->returnDatabase());

    o = createOrders(d, o);

    std::vector<std::tuple<float, float>> locList = d->getLocList();
    for (auto& it : locList) {
        aLocs.append(QPointF(std::get<0>(it) * TILE_SIZE/SCALE, std::get<1>(it) * TILE_SIZE/SCALE));
    }

    // iterates through the product list
    // and check the productID and positions of each product
    // also adds the products to the adjacency matrix
    std::list<Product> l = o.getProductList();
    std::deque<Product> deq;
    for (auto& it:l) {
        deq.push_back(it);
        std::cout << "ID: " << it.getProductID() << "\txPosition: " << it.getXPosition()
            << "\tyPosition: " << it.getYPosition() << std::endl;
        pLocs.append(QPointF(it.getXPosition() * TILE_SIZE/SCALE, it.getYPosition() * TILE_SIZE/SCALE));
    }

    Inventory inventory(aLocs, pLocs);

    std::cout << "product list size: " << pLocs.size() << std::endl;
    std::cout << "all list size: " << aLocs.size() << std::endl;

    std::tuple<float, float> startLocation = std::make_tuple(0,0);
    std::tuple<float, float> endLocation = std::make_tuple(40,21);

    Product dummyStart("startLocation", startLocation);
    Product dummyEnd("endLocation", endLocation);

    //deq.push_back(dummyStart);
    matrix.setProductList(deq);
    matrix.populateMatrix();
    matrix.displayMatrix();

    MainWindow w;
    w.loadAllPoints(aLocs);
    w.loadProductPoints(pLocs);
    w.setFixedSize(1500, 1000);
    w.setWindowTitle("Main Warehouse Map with Path");

    std::cout << "Please wait; calculating path." << std::endl;

    std::deque<Product> path = pathFinder.calculatePath(matrix.getMatrix(),deq,dummyStart,dummyEnd);
    std::cout<<"Path for you : ";

    QVector<QPointF> route = pathFinder.displayPath();
    std::cout<<std::endl;
    QVector <std::string> instructions = pathFinder.pathAnnotation(path);

    for (auto& instruction: instructions) {
        std::cout << instruction << std::endl;
    }

    w.loadInstructions(instructions);
    w.loadRoutePrinter(route);
    w.show();
    return a.exec();
}


Order createOrders(Database* d, Order o) {
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

    t = d->getProductPosition("290");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("290", t);
    o.addProduct(p);

    t = d->getProductPosition("485");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("485", t);
    o.addProduct(p);

    t = d->getProductPosition("364");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("364", t);
    o.addProduct(p);

    t = d->getProductPosition("571");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("571", t);
    o.addProduct(p);

    t = d->getProductPosition("517");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("517", t);
    o.addProduct(p);

    t = d->getProductPosition("623");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("623", t);
    o.addProduct(p);

    t = d->getProductPosition("3401");
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    p.~Product();

    new(&p) Product("3401", t);
    o.addProduct(p);

    return o;
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
