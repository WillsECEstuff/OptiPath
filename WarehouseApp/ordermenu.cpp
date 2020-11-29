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
#include "NN.h"
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
    //ui->setupUi(this);
    txtOrder = new QLabel(this);
    QFont font = txtOrder->font();
    font.setPointSize(25);
    txtOrder->setText("Orders");
    txtOrder->setFont(font);
    txtOrder->setGeometry(235,80,110,50);
    ordercbox = new QComboBox(this);
    ordercbox->setGeometry(200,150,180,25);
    ordercbox->addItem("Select an order...");

    settingsButton = new QPushButton("Settings", this);
    settingsButton->setGeometry(100,200,135,50);
    routeButton = new QPushButton("Show Route", this);
    routeButton->setGeometry(345,200,135,50);
    addOrderButton = new QPushButton("Create Order", this);
    addOrderButton->setGeometry(100,300,135,50);
    enterSingleButton = new QPushButton("Search for Single Product/\nMap Preview", this);
    enterSingleButton->setGeometry(345,300,135,50);

    txtLblOrder = new QLabel(this);
    txtLblOrder->setText("Add product ID(s) below\nfollowing the example below,\nthen click on 'Create Order.'\nLeave empty to get order list\nfrom a file.");
    txtLblOrder->setGeometry(100,360,300,75);
    txtAddOrder = new QLineEdit(this);
    txtAddOrder->setPlaceholderText("123, 456, 789");
    txtAddOrder->setGeometry(100,435,135,25);

    txtLblSingle = new QLabel(this);
    txtLblSingle->setText("Just want a single product?\nEnter a single product ID below,\nthen click on 'Search for Single Product.'\nLeave empty for map preview.");
    txtLblSingle->setGeometry(345,360,300,75);
    txtwantsingle = new QLineEdit(this);
    txtwantsingle->setPlaceholderText("123");
    txtwantsingle->setGeometry(390,435,50,25);

    connect(routeButton, SIGNAL (clicked()), this, SLOT (handleRouteButton()));
    connect(enterSingleButton, SIGNAL(clicked()), this, SLOT(handleSingleButton()));
    connect(addOrderButton, SIGNAL(clicked()), this, SLOT(handleCreateOrderButton()));
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(handleSettingsButton()));

    Database *d = d->getInstance();

    // store all points from database
    std::vector<std::tuple<float, float>> locList = d->getLocList();
    for (auto& it : locList) {
        allPoints.append(QPointF(std::get<0>(it), std::get<1>(it)));
    }

    startLocation = std::make_tuple(0,0);
    endLocation = std::make_tuple(0,0);
}

ordermenu::~ordermenu()
{
    delete ui;
}

/**
 * @brief   button handler when pressed "Return to order menu"
 * 
 */
void ordermenu::onOtherSignal() {
    show();
}

/**
 * @brief   button handler when pressed complete order
 * 
 */
void ordermenu::onOrderCompleteSignal() {
    orderList[currentOrderIDx - 1].orderCompleted();
    show();
}

void ordermenu::onSettingsSignal() {
    myTimer = settingsWindow->getTimer();
    startLocation = settingsWindow->getSLocation();
    endLocation = settingsWindow->getELocation();
    std::cout << "startLocation: " << std::get<0>(startLocation) << "," << std::get<1>(startLocation) << std::endl;
    std::cout << "endLocation: " << std::get<0>(endLocation) << "," << std::get<1>(endLocation) << std::endl;
    std::cout << "timer: " << myTimer << std::endl;
    settingsWindow->close();
    show();
}

void ordermenu::handleSettingsButton() {
    settingsWindow = new settingsmenu();
    connect (settingsWindow, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));
    connect (settingsWindow, SIGNAL(fromSettingsMenu()), this, SLOT(onSettingsSignal()));
    settingsWindow->setTimer(myTimer);
    settingsWindow->setSLocation(startLocation);
    settingsWindow->setELocation(endLocation);
    settingsWindow->setTextFields();

    settingsWindow->setFixedSize(575, 700);
    settingsWindow->setWindowTitle("Settings");
    this->hide();
    settingsWindow->show();
}

void ordermenu::handleRouteButton() {
    Database *d = d->getInstance();
    routePoints.clear();
    productPoints.clear();
    directions.clear();

    currentOrderIDx = ordercbox->currentIndex();
    std::cout << "Current COMBOBOX index: " << currentOrderIDx << std::endl;

    routeMap = new mainwhmap();
    connect (routeMap, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));
    connect (routeMap, SIGNAL(COB()), this, SLOT(onOrderCompleteSignal()));

    if (currentOrderIDx < 1) {
        QMessageBox notifyUser;
        notifyUser.setText("Please select an order from the drop-down menu.");
        notifyUser.setWindowTitle("Error - Couldn't Read Order");
        notifyUser.exec();
    }

    else {
        Order o = orderList[currentOrderIDx -1];
        Order::Status stat = o.getOrderStatus();

        std::list<Product> l = o.getProductList();
        std::deque<Product> deq;
        for (auto& it:l) {
            deq.push_back(it);
            std::cout << "ID: " << it.getProductID() << "\txPosition: " << it.getXPosition()
                << "\tyPosition: " << it.getYPosition() << std::endl;
            productPoints.append(QPointF(it.getXPosition(),  it.getYPosition() ));
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
        NN NNFinder;
        routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd,myTimer);
        //routePoints = pathFinder.ReturnTraversal(deq,dummyStart,dummyEnd, myTimer);
        //routePoints = NNFinder.NNAlgorithm(deq,dummyStart,dummyEnd,myTimer);

        //routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd,myTimer);
        std::cout << "routePoints size: " << routePoints.size() << std::endl;

        std::cout<<"Points to be reached are:"<<std::endl;
        for(auto& point : routePoints) {
            std::cout<<"("<<point.rx()/6<<","<<point.ry()/6<<")"<<std::endl;
        }


        directions = pathFinder.pathAnnotation();
        for (auto& instruction: directions) {
            std::cout << instruction << std::endl;
        }


        //std::cout << "test" << std::endl;
        //routeMap->loadAllPoints(allPoints);
        routeMap->loadUnconvertedPoints(allPoints);
        //routeMap->loadProductPoints(productPoints);
        routeMap->loadUnconvertedProductPoints(productPoints);
        //routeMap->loadRoutePrinter(routePoints);
        //routeMap->loadUnconvertedRoutePrinter(routePoints);
        routeMap->loadUnconvertedPointsPF(pathFinder.getPoints());
        routeMap->loadInstructions(directions);
        routeMap->loadOrderStatus(stat);
        routeMap->setFixedSize(1500, 800);
        routeMap->setWindowTitle("Warehouse Map with Route");
        this->hide();
        routeMap->show();
    }
}

void ordermenu::handleCreateOrderButton() {
    std::string order = txtAddOrder->text().toStdString();
    int orderIdx = ordercbox->count();
    int priority = 1;
    std::vector<Order> tempOrderList;

    if (order == "") { // user tried to enter an empty order
        std::string path;

        QMessageBox notifyUser;
        QMessageBox::StandardButton reply;
        std::string orderWarn = "Your order is currently empty. Do you want to create an order(s) from a file instead?";
        reply = QMessageBox::question(this, "Empty Order", QString::fromStdString(orderWarn), QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QString qs = QFileDialog::getOpenFileName(NULL,
                QObject::tr("Open Order File"),"/home",
                QObject::tr("Text File (*.txt)"));
            path = qs.toStdString();

            tempOrderList = createOrdersfromFile(path, orderIdx, priority);

            std::vector<Order>::iterator it;

            for (it = tempOrderList.begin(); it != tempOrderList.end(); it++) {
                orderList.push_back(*it);
                size_t orderSize = it->getSize();
                std::string pinnedOrder = "Order #" + std::to_string(orderList.size()) + ", containing " + std::to_string(orderSize) + " items";
                ordercbox->addItem(QString::fromStdString(pinnedOrder));
            }

            if (tempOrderList.size() == 0) {
                std::string notify = std::to_string(tempOrderList.size()) + " orders added from file. File may be incorrectly formatted.";
                notifyUser.setWindowTitle("No Orders Created");
                notifyUser.setText(QString::fromStdString(notify));
            }

            else {
                std::string notify = std::to_string(tempOrderList.size()) + " orders added from file.";
                notifyUser.setWindowTitle("Orders Successfully Created");
                notifyUser.setText(QString::fromStdString(notify));
            }

            notifyUser.exec();
        }

        else {
            std::string notify = "Your order is currently empty!";
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Error - Empty Order");
            notifyUser.exec();
        }
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
        size_t orderSize = o.getSize();
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
        std::string pinnedOrder = "Order #" + std::to_string(orderNum) + ", containing " + std::to_string(orderSize) + " items";
        ordercbox->addItem(QString::fromStdString(pinnedOrder));

        std::string notify = pinnedOrder + "\nContents: " + chain;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Order Created");
        notifyUser.exec();

        std::cout << "big order size: " << orderList.size() << std::endl;
        int idx = orderList.size() - 1;
        std::cout << "order size: " << orderList[idx].getSize() << std::endl;
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
    int height = 22;

    secWindow = new secondProductWindow();
    connect (secWindow, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));

    if (ID == "") { // map preview
        //secWindow->loadAllPoints(allPoints);
        secWindow->loadUnconvertedPoints(allPoints);
        QPointF startPt, endPt;

        float xS = std::get<0>(startLocation);
        float yS = std::get<1>(startLocation);
        float xE = std::get<0>(endLocation);
        float yE = std::get<1>(endLocation);

        startPt.setX(xS * TILE_SIZE/SCALE);
        startPt.setY(( (float) height - yS) * TILE_SIZE/SCALE);
        endPt.setX(xE * TILE_SIZE/SCALE);
        endPt.setY(((float)height - yE) * TILE_SIZE/SCALE);

        routePoints.push_back(startPt);
        routePoints.push_back(endPt);
        secWindow->loadRoutePrinter(routePoints);
        //secWindow->loadUnconvertedRoutePrinter(routePoints);
        secWindow->setFixedSize(1500, 800);
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

        //Product dummyStart("startLocation", startLocation);
        //Product dummyEnd("endLocation", endLocation);
        //PathFinder pathFinder;
        //routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd, myTimer);

        //directions = pathFinder.pathAnnotation();

        //for (auto& instruction: directions) {
        //    std::cout << instruction << std::endl;
        //}

        //secWindow->loadAllPoints(allPoints);
        //secWindow->loadProductPoint(ID);
        //secWindow->loadRoutePrinter(routePoints);
        //secWindow->loadInstructions(directions);
        //secWindow->setPreview(false);
        //secWindow->setFixedSize(1500, 1000);
        //secWindow->setWindowTitle("Single Product Map");

        //this->hide();

        QMessageBox notifyUser;
        //std::string notify = "Product Location: " + std::to_string(p.getXPosition()) + ", " +  std::to_string(p.getYPosition()) + "\nClick to see map.";
        std::string notify = "Product Location: " + std::to_string(p.getXPosition()) + ", " + std::to_string(p.getYPosition());
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Selected Product Location");
        notifyUser.exec();

        //secWindow->show();
    }
}
