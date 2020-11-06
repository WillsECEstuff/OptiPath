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

const float TILE_SIZE = 30;
const float SCALE = 5;

ordermenu::ordermenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ordermenu)
{
    //ui->setupUi(this);
    settingsButton = new QPushButton("Settings", this);
    settingsButton->setGeometry(100,200,135,50);
    routeButton = new QPushButton("Show Route", this);
    routeButton->setGeometry(345,200,135,50);
    locationButton = new QPushButton("Change Starting Location", this);
    locationButton->setGeometry(100,300,135,50);
    enterSingleButton = new QPushButton("Search for Single Product/\nMap Preview", this);
    enterSingleButton->setGeometry(345,300,135,50);

    addOrderButton = new QPushButton("Create Order", this);
    addOrderButton->setGeometry(235,480,135,50);
    addProdButton = new QPushButton("Add Product", this);
    addProdButton->setGeometry(235,650,135,50);

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
    txtLblOrder->setText("Keep entering Product ID(s) below\nand click 'Add Product' to continue making the order,\nthen click on 'Create Order' when finished.");
    txtLblOrder->setGeometry(235,540,300,50);
    txtAddOrder = new QLineEdit(this);
    txtAddOrder->setPlaceholderText("123");
    txtAddOrder->setGeometry(280,605,50,25);

    txtLblLoc = new QLabel(this);
    txtLblLoc->setText("Enter a location below\nas (x,y) without parentheses,\nthen click on 'Change Starting Location.'\nThis also sets ending location.");
    txtLblLoc->setGeometry(100,360,300,60);
    txtLoc = new QLineEdit(this);
    txtLoc->setPlaceholderText("0,0");
    txtLoc->setGeometry(145,425,50,25);

    txtLblSingle = new QLabel(this);
    txtLblSingle->setText("Just want a single product?\nEnter a single product ID below,\nthen click on 'Search for Single Product.'\nLeave empty for map preview.");
    txtLblSingle->setGeometry(345,360,300,60);
    txtwantsingle = new QLineEdit(this);
    txtwantsingle->setPlaceholderText("123");
    txtwantsingle->setGeometry(390,425,50,25);

    connect(routeButton, SIGNAL (clicked()), this, SLOT (handleRouteButton()));
    connect(locationButton, SIGNAL (clicked()), this, SLOT (handleLocationButton()));
    connect(enterSingleButton, SIGNAL(clicked()), this, SLOT(handleSingleButton()));

    connect(addProdButton, SIGNAL(clicked()), this, SLOT(handleAddProductButton()));
    connect(addOrderButton, SIGNAL(clicked()), this, SLOT(handleCreateOrderButton()));

    Database *d = d->getInstance();

    // store all points from database
    std::vector<std::tuple<float, float>> locList = d->getLocList();
    for (auto& it : locList) {
        allPoints.append(QPointF(std::get<0>(it) * TILE_SIZE/SCALE, std::get<1>(it) * TILE_SIZE/SCALE));
    }

    startLocation = std::make_tuple(0,1);
    endLocation = std::make_tuple(0,1);
}

ordermenu::~ordermenu()
{
    delete ui;
}
/*
void ordermenu::loadAllPoints(QVector <QPointF> ptsList) {
    allPoints = ptsList;
    std::cout << "loaded all" << std::endl;
}

void ordermenu::loadProductPoints(QVector <QPointF> ptsList) {
    productPoints = ptsList;
    std::cout << "loaded products" << std::endl;
}

void ordermenu::loadRoutePrinter(QVector<QPointF> route) {
    routePoints = route;
    std::cout << "loaded route" << std::endl;
}

void ordermenu::loadInstructions(QVector<std::string> instrList) {
    directions = instrList;
    std::cout << "loaded instructions" << std::endl;
} */

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
        Order o(orderIdx, orderIdx);
        processOrder(&o, d, orderIdx);

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

        PathFinder pathFinder;
        routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd);

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

void ordermenu::processOrder(Order *o, Database *db, int oIdx) {
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
}

void ordermenu::handleLocationButton() {
    std::string sLoc = txtLoc->text().toStdString();
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
            endLocation = startLocation;

            std::cout << "Start X = " << std::get<0>(startLocation) << ", start Y = " << std::get<1>(startLocation) << std::endl;
            std::cout << "End X = " << std::get<0>(endLocation) << ", end Y = " << std::get<1>(endLocation) << std::endl;

            QMessageBox notifyUser;
            std::string notify = "Location entered successfully. X = " + std::to_string(std::get<0> (startLocation)) + ", Y = " + std::to_string(std::get<1> (startLocation));
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Success - Entered Location");
            notifyUser.exec();
        }
    }
}

void ordermenu::handleCreateOrderButton() {
    if (prodIDs.size() == 0) { // user tried to enter an empty order
        QMessageBox notifyUser;
        notifyUser.setText("Your order is currently empty!");
        notifyUser.setWindowTitle("Error - Empty Order");
        notifyUser.exec();
    }

    else {
        orderList.push_back(prodIDs);
        std::string chain = "";
        int orderNum = orderList.size();

        for (int i = 0; i < prodIDs.size(); i++) {
            std::string temp = prodIDs[i] + " | ";
            chain = chain + temp;
        }

        QMessageBox notifyUser;
        std::string pinnedOrder = "Order " + std::to_string(orderNum) + ", containing " + std::to_string(prodIDs.size());
        ordercbox->addItem(QString::fromStdString(pinnedOrder));

        std::string notify = pinnedOrder + " products\nContents: " + chain;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Order Created");
        prodIDs.clear();
        notifyUser.exec();

        std::cout << "big order size: " << orderList.size() << std::endl;
        int idx = orderList.size() - 1;
        std::cout << "order size: " << orderList[idx].size() << std::endl;
    }
}

void ordermenu::handleAddProductButton() {
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
        routePoints = pathFinder.STraversal(deq,dummyStart,dummyEnd);

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
