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
#include "mainwhmap.h"
#include "Inventory.h"
#include "WarehouseMap.h"
#include <QDir>
#include <QDebug>
#include "ordermenu.h"

void fillOrderDriver(Order* o, Database* d);
void instantiateGUIs(QVector<QPointF> aLocs, QVector<QPointF> pLocs, QVector<QPointF> pointsToDisplay);

int main(int argc, char** argv)
{
    qDebug() << QDir().currentPath(); // verify that the warehouse .txt file is in the path!
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    // Instantiate a database
    // only expected 1 instance
    Database* d = d->getInstance();
    WarehouseMap* whm = whm->getInstance();

    // Instantiate an adjacency matrix
    AdjacencyMatrix matrix;

    // make sure database is clear before reading and populating
    // database from the text file
    d->deleteDatabase();
    std::string path = "qvBox-warehouse-data-f20-v01.txt";
    while (d->isDatabaseEmpty()) {
        try {
            d->populateDatabase(path);
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            QString msg(ex.what());
            QMessageBox msgBox;
            msgBox.setText(msg);
            msgBox.exec();
            
            
            QString qs = QFileDialog::getOpenFileName(NULL,
                QObject::tr("Open Database File"), a.applicationDirPath(), 
                QObject::tr("Text File (*.txt)"));
            path = qs.toStdString();
            
        }
    }
    

    whm->buildWarehouseMap(d->returnDatabase());
    json j = whm->getShelves();
    std::cout << j.dump(4) << std::endl;

    // load GUIs begin
    ordermenu om;
    om.setFixedSize(600, 850);
    om.setWindowTitle("Order Menu");
    om.show();
    // load GUIs end
    return a.exec();
}

    /* UNUSED
    matrix.setProductList(deq);
    matrix.populateMatrix();
    matrix.displayMatrix();

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
    */
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
