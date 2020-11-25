/*****************************************************************//**
 * @file   ordermenu.cpp
 * @brief  This file is contains the definitions for ordermenu.h
 * @date   November 2020
 *********************************************************************/


#include "ordermenu.h"
#include "ui_ordermenu.h"
#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QtWidgets>
#include <iostream>
#include "Database.h"
#include <QString>
#include <stdlib.h>
#include <QMessageBox>
#include "Ticket.h"
#include "Order.h"
#include "PathFinder.h"
#include "OrderHelper.h"

#ifdef _DEBUG

#include "MST.h"

#endif

const float TILE_SIZE = 30;
const float SCALE = 5;

ordermenu::ordermenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ordermenu)
{

    //
    //ui->setupUi(this);
    settingsButton = new QPushButton("Settings", this);
    settingsButton->setGeometry(100,200,135,50);
    routeButton = new QPushButton("Show Route", this);
    routeButton->setGeometry(345,200,135,50);
    startLocationButton = new QPushButton("Change Starting Location", this);
    startLocationButton->setGeometry(100,300,135,50);
    enterSingleButton = new QPushButton("Search for Single Product/\nMap Preview", this);
    enterSingleButton->setGeometry(345,300,135,50);
    endLocationButton = new QPushButton("Change Ending Location", this);
    endLocationButton->setGeometry(100,480,135,50);

    addOrderButton = new QPushButton("Create Order", this);
    addOrderButton->setGeometry(345,480,135,50);
    timerButton = new QPushButton("Change timer", this);
    timerButton->setGeometry(235,660,110,50);

    txtLblTimer = new QLabel(this);
    txtLblTimer->setText("Change the timer below,\nin seconds.");
    txtLblTimer->setGeometry(235,720,300,40);
    txtTimer = new QLineEdit(this);
    txtTimer->setPlaceholderText("60.0");
    txtTimer->setGeometry(265,765,50,25);

    txtOrder = new QLabel(this);
    QFont font = txtOrder->font();
    font.setPointSize(25);
    txtOrder->setText("Orders");
    txtOrder->setFont(font);
    txtOrder->setGeometry(235,80,110,50);
    ordercbox = new QComboBox(this);
    ordercbox->setGeometry(210,150,160,25);
    ordercbox->addItem("Select an order...");

    txtLblOrder = new QLabel(this);
    txtLblOrder->setText("Add product ID(s) below\nfollowing the example below,\nthen click on 'Create Order.'");
    txtLblOrder->setGeometry(345,540,300,60);
    txtAddOrder = new QLineEdit(this);
    txtAddOrder->setPlaceholderText("123, 456, 789");
    txtAddOrder->setGeometry(345,605,135,25);

    txtLblSLoc = new QLabel(this);
    txtLblSLoc->setText("Enter a location below\nas (x,y) without parentheses,\nthen click on\n'Change Starting Location.'");
    txtLblSLoc->setGeometry(100,360,300,60);
    txtSLoc = new QLineEdit(this);
    txtSLoc->setPlaceholderText("0,0");
    txtSLoc->setGeometry(145,425,50,25);

    txtLblELoc = new QLabel(this);
    txtLblELoc->setText("Enter a location below\nas (x,y) without parentheses,\nthen click on\n'Change Ending Location.'");
    txtLblELoc->setGeometry(100,540,300,60);
    txtELoc = new QLineEdit(this);
    txtELoc->setPlaceholderText("0,0");
    txtELoc->setGeometry(145,605,50,25);

    txtLblSingle = new QLabel(this);
    txtLblSingle->setText("Just want a single product?\nEnter a single product ID below,\nthen click on 'Search for Single Product.'\nLeave empty for map preview.");
    txtLblSingle->setGeometry(345,360,300,60);
    txtwantsingle = new QLineEdit(this);
    txtwantsingle->setPlaceholderText("123");
    txtwantsingle->setGeometry(390,425,50,25);

    connect(routeButton, SIGNAL (clicked()), this, SLOT (handleRouteButton()));
    connect(startLocationButton, SIGNAL (clicked()), this, SLOT (handleSLocationButton()));
    connect(endLocationButton, SIGNAL (clicked()), this, SLOT (handleELocationButton()));
    connect(enterSingleButton, SIGNAL(clicked()), this, SLOT(handleSingleButton()));
    connect(timerButton, SIGNAL(clicked()), this, SLOT(handleTimerButton()));
    connect(addOrderButton, SIGNAL(clicked()), this, SLOT(handleCreateOrderButton()));

    Database *d = d->getInstance();

    // store all points from database
    std::vector<std::tuple<float, float>> locList = d->getLocList();
    for (auto& it : locList) {
        allPoints.append(QPointF(std::get<0>(it) * TILE_SIZE/SCALE, std::get<1>(it) * TILE_SIZE/SCALE));
    }

    startLocation = std::make_tuple(0,0);
    endLocation = std::make_tuple(0,0);
}

ordermenu::~ordermenu()
{
    delete ui;
}

void ordermenu::onOtherSignal() {
    show();
}

void ordermenu::handleRouteButton() {
    Database *d = d->getInstance();
    routePoints.clear();
    productPoints.clear();
    directions.clear();

    int orderIdx = ordercbox->currentIndex();
    std::cout << "Current COMBOBOX index: " << orderIdx << std::endl;

    routeMap = new mainwhmap();
    connect (routeMap, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));

    if (orderIdx < 1) {
        QMessageBox notifyUser;
        notifyUser.setText("Please select an order from the drop-down menu.");
        notifyUser.setWindowTitle("Error - Couldn't Read Order");
        notifyUser.exec();
    }

    else {
        Order o = orderList[orderIdx-1];
        //processOrder(&o, d, orderIdx);

        std::list<Product> l = o.getProductList();
        std::deque<Product> deq;
        for (auto& it:l) {
            deq.push_back(it);
            std::cout << "ID: " << it.getProductID() << "\txPosition: " << it.getXPosition()
                << "\tyPosition: " << it.getYPosition() << std::endl;
            productPoints.append(QPointF(it.getXPosition() * TILE_SIZE/SCALE, it.getYPosition() * TILE_SIZE/SCALE));
        }

        Product dummyStart("startLocation", startLocation);
        Product dummyEnd("endLocation", endLocation);
        std::cout << "starting: " << dummyStart.getXPosition() << ", " << dummyStart.getYPosition() << std::endl;

#ifdef _DEBUG

        MST mst(o, dummyEnd);
        mst.printAdjacencyMatrix();
        std::cout << "Lower bound is: " <<
            mst.findLowerBound() << std::endl;

#endif // 

        PathFinder pathFinder;
        routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd, myTimer);
        std::cout << "routePoints size: " << routePoints.size() << std::endl;

        std::cout<<"Points to be reached are:"<<std::endl;
        for(auto& point : routePoints) {
            std::cout<<"("<<point.rx()/6<<","<<point.ry()/6<<")"<<std::endl;
        }

        directions = pathFinder.pathAnnotation();

        for (auto& instruction: directions) {
            std::cout << instruction << std::endl;
        }

        std::cout << "test" << std::endl;
        routeMap->loadAllPoints(allPoints);
        routeMap->loadProductPoints(productPoints);
        routeMap->loadRoutePrinter(routePoints);
        routeMap->loadInstructions(directions);
        routeMap->setFixedSize(1500, 1000);
        routeMap->setWindowTitle("Warehouse Map with Route");
        this->hide();
        routeMap->show();
    }
}

/*void ordermenu::processOrder(Order *o, Database *db, int oIdx) {
    // Instantiate an order
    QVector<std::string> orderContents = orderList[oIdx-1];
    std::cout << orderContents.size() << std::endl;

    for (int i = 0; i < orderContents.size(); i++) {
        std::tuple<float, float> t = db->getProductPosition(orderContents[i]);
        std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;

        // create a product class
        // and add the product into the order
        Product p(orderContents[i], t);
        o->addProduct(p);
        p.~Product();
    }
} */

void ordermenu::handleSLocationButton() {
    std::string sLoc = txtSLoc->text().toStdString();
    int idx = (int)sLoc.find(",");
    std::string xLoc = sLoc.substr(0, idx);
    std::string yLoc = sLoc.substr(idx+1);
    std::string notify = "Please enter a valid location (0 <= X <= 40, 0 <= Y <= 22). Y must be odd; even Y is a shelf.";

    float x = 0, y = 0;

    if (isdigit(xLoc[0]) == 0 || isdigit(yLoc[0]) == 0) { // not a number
        QMessageBox notifyUser;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Error - Entered Location");
        notifyUser.exec();
    }

    else {
        x = stof(xLoc);
        y = stof(yLoc);

        int ycheck = (int)y;

        if (x < 0 || x > 40 || y < 0 || y > 22 || idx == -1 || ycheck % 2 == 0) { // out of bounds/invalid
            QMessageBox notifyUser;
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Error - Entered Location");
            notifyUser.exec();
        }

        else {
            std::get<0>(startLocation) = x;
            std::get<1>(startLocation) = y;

            std::cout << "Start X = " << std::get<0>(startLocation) << ", start Y = " << std::get<1>(startLocation) << std::endl;

            QMessageBox notifyUser;
            std::string notify = "Location entered successfully. X = " + std::to_string(std::get<0> (startLocation)) + ", Y = " + std::to_string(std::get<1> (startLocation));
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Success - Entered Location");
            notifyUser.exec();
        }
    }
}

void ordermenu::handleELocationButton() {
    std::string eLoc = txtELoc->text().toStdString();
    int idx = (int)eLoc.find(",");
    std::string xLoc = eLoc.substr(0, idx);
    std::string yLoc = eLoc.substr(idx+1);
    std::string notify = "Please enter a valid location (0 <= X <= 40, 0 <= Y <= 22). Y must be odd; even Y is a shelf.";

    float x = 0, y = 0;

    if (isdigit(xLoc[0]) == 0 || isdigit(yLoc[0]) == 0) { // not a number
        QMessageBox notifyUser;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Error - Entered Location");
        notifyUser.exec();
    }

    else {
        x = stof(xLoc);
        y = stof(yLoc);

        int ycheck = (int)y;

        if (x < 0 || x > 40 || y < 0 || y > 22 || idx == -1 || ycheck % 2 == 0) { // out of bounds/invalid
            QMessageBox notifyUser;
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Error - Entered Location");
            notifyUser.exec();
        }

        else {
            std::get<0>(endLocation) = x;
            std::get<1>(endLocation) = y;

            std::cout << "End X = " << std::get<0>(endLocation) << ", end Y = " << std::get<1>(endLocation) << std::endl;

            QMessageBox notifyUser;
            std::string notify = "Location entered successfully. X = " + std::to_string(std::get<0> (endLocation)) + ", Y = " + std::to_string(std::get<1> (endLocation));
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Success - Entered Location");
            notifyUser.exec();
        }
    }
}

void ordermenu::handleCreateOrderButton() {
    std::string order = txtAddOrder->text().toStdString();

    if (order == "") { // user tried to enter an empty order
        QMessageBox notifyUser;
        notifyUser.setText("Your order is currently empty!");
        notifyUser.setWindowTitle("Error - Empty Order");
        notifyUser.exec();
    }

    else if (order.find_first_not_of("1234567890, ") != std::string::npos) {
        QMessageBox notifyUser;
        notifyUser.setText("Your order contains invalid characters!");
        notifyUser.setWindowTitle("Error - Invalid Order");
        notifyUser.exec();
    }

    else {
        int orderIdx = ordercbox->count(); // temporary; this is always at least 1 + number of orders in the system before
        Order o;
        std::cout << order << std::endl;
        o = createOrderfromString(order, orderIdx, orderIdx);
        int orderSize = o.getSize();
        std::list<Product> tempPList = o.getProductList();

        if (o.getSize() == 0) {
            QMessageBox notifyUser;
            notifyUser.setText("Your order had invalid products, so it's empty!");
            notifyUser.setWindowTitle("Error - Empty Order");
            notifyUser.exec();
            return;
        }

        orderList.push_back(o);
        std::string chain = "";
        int orderNum = orderList.size(); // this is always the number of orders now in the system (at least 1 at this point)

        std::cout << "ordersize now: " << orderSize << std::endl;
        std::list<Product>::iterator it;

        for (it = tempPList.begin(); it != tempPList.end(); it++) {
            std::string temp = it->getProductID() + " | ";
            chain = chain + temp;
        }

        QMessageBox notifyUser;
        std::string pinnedOrder = "Order " + std::to_string(orderNum) + ", containing " + std::to_string(orderSize);
        ordercbox->addItem(QString::fromStdString(pinnedOrder));

        std::string notify = pinnedOrder + " products\nContents: " + chain;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Order Created");
        //prodIDs.clear();
        notifyUser.exec();

        std::cout << "big order size: " << orderList.size() << std::endl;
        int idx = orderList.size() - 1;
        std::cout << "order size: " << orderList[idx].getSize() << std::endl;
    }
}

/*void ordermenu::handleAddProductButton() {
    Database *d = d->getInstance();
    std::string ID = txtAddOrder->text().toStdString();
    std::tuple<float, float> t;
    t = d->getProductPosition(ID);
    float x = std::get<0>(t);
    float y = std::get<1>(t);
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    if (x == 1 || y == -1 || prodIDs.contains(ID)) {
        QMessageBox notifyUser;
        notifyUser.setText("Please enter a unique and valid product ID!");
        notifyUser.setWindowTitle("Error - Invalid ID");
        notifyUser.exec();
    }

    else {
        prodIDs.push_back(ID);
        QMessageBox notifyUser;
        std::string chain = "";

        for (int i = 0; i < prodIDs.size(); i++) {
            std::string temp = prodIDs[i] + " | ";
            chain = chain + temp;
        }

        std::string notify = "Currently building order with: " + chain + "\nAdded product ID " + ID + " with location 'X,Y' as " + std::to_string(x) + "," + std::to_string(y) +".\nRemember to click Add Order when done.";
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Success - Adding Product ID");
        notifyUser.exec();
    }
} */

void ordermenu::handleTimerButton() {
    std::string num = txtTimer->text().toStdString();

    if (num.find_first_not_of("1234567890.") != std::string::npos) { // If any other characters are detected, generate an error
        QMessageBox notifyUser;
        notifyUser.setText("Please enter a valid time, in seconds.");
        notifyUser.setWindowTitle("Error - Invalid Timer");
        notifyUser.exec();
    }

    else {
        QMessageBox notifyUser;
        myTimer = stof(num);
        std::string notify = "Timer had been set to " + std::to_string(myTimer) + " seconds.";
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Success - Timer Set");
        notifyUser.exec();
    }
}

void ordermenu::handleSingleButton() {
    Database *d = d->getInstance();
    routePoints.clear();
    directions.clear();
    std::string ID = txtwantsingle->text().toStdString();
    std::tuple<float, float> isReal = d->getProductPosition(ID);
    float x = std::get<0>(isReal);
    float y = std::get<1>(isReal);

    secWindow = new secondProductWindow();
    connect (secWindow, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));

    if (ID == "") { // map preview
        secWindow->loadAllPoints(allPoints);
        QPointF startPt, endPt;

        float xS = std::get<0>(startLocation);
        float yS = std::get<1>(startLocation);
        float xE = std::get<0>(endLocation);
        float yE = std::get<1>(endLocation);

        startPt.setX(xS * TILE_SIZE/SCALE);
        startPt.setY(yS * TILE_SIZE/SCALE);
        endPt.setX(xE * TILE_SIZE/SCALE);
        endPt.setY(yE * TILE_SIZE/SCALE);

        routePoints.push_back(startPt);
        routePoints.push_back(endPt);
        secWindow->loadRoutePrinter(routePoints);
        secWindow->setFixedSize(1500, 1000);
        secWindow->setWindowTitle("Map Preview");
        secWindow->setPreview(true);
        this->hide();
        secWindow->show();
    }

    else if (x == -1 || y == -1) {
        // Prompt user with an error message.
        QMessageBox notifyUser;
        notifyUser.setText("Please enter a valid product ID!");
        notifyUser.setWindowTitle("Error - Invalid ID");
        notifyUser.exec();
    }

    else { // show the route and message box
        std::deque<Product> deq;
        Product p(ID, isReal);
        deq.push_back(p);

        Product dummyStart("startLocation", startLocation);
        Product dummyEnd("endLocation", endLocation);
        PathFinder pathFinder;
        routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd, myTimer);

        directions = pathFinder.pathAnnotation();

        for (auto& instruction: directions) {
            std::cout << instruction << std::endl;
        }

        secWindow->loadAllPoints(allPoints);
        secWindow->loadProductPoint(ID);
        secWindow->loadRoutePrinter(routePoints);
        secWindow->loadInstructions(directions);
        secWindow->setPreview(false);
        secWindow->setFixedSize(1500, 1000);
        secWindow->setWindowTitle("Single Product Map");

        this->hide();

        QMessageBox notifyUser;
        std::string notify = "Product Location: " + std::to_string(p.getXPosition()) + ", " +  std::to_string(p.getYPosition()) + "\nClick to see map.";
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Selected Product Location");
        notifyUser.exec();

        secWindow->show();
    }
}
