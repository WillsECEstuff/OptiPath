#include "ordermenu.h"
#include "ui_ordermenu.h"
#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QtWidgets>
#include <iostream>
#include "Database.h"

ordermenu::ordermenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ordermenu)
{
    //ui->setupUi(this);
    routeButton = new QPushButton("Show Route", this);
    routeButton->setGeometry(100,200,135,50);
    allWHMapButton = new QPushButton("Show Warehouse Map", this);
    allWHMapButton->setGeometry(345,200,135,50);
    settingsButton = new QPushButton("Settings", this);
    settingsButton->setGeometry(100,300,135,50);
    enterSingleButton = new QPushButton("Search for Single Product", this);
    enterSingleButton->setGeometry(345,300,135,50);

    txtOrder = new QLabel(this);
    QFont font = txtOrder->font();
    font.setPointSize(25);
    txtOrder->setText("Orders");
    txtOrder->setFont(font);
    txtOrder->setGeometry(235,80,110,50);
    ordercbox = new QComboBox(this);
    ordercbox->setGeometry(235,150,110,25);
    ordercbox->addItem("Select an order...");


    txtLbl = new QLabel(this);
    txtLbl->setText("Don't want to select an order?\nEnter a single product ID below,\nthen click on 'Search for Single Product.'");
    txtLbl->setGeometry(345,375,300,40);
    txtwantsingle = new QLineEdit(this);
    txtwantsingle->setPlaceholderText("123");
    txtwantsingle->setGeometry(390,425,50,25);
    txtwantsingle->setFocus();

    connect(routeButton, SIGNAL (clicked()), this, SLOT (handleRouteButton()));
    connect(allWHMapButton, SIGNAL (clicked()), this, SLOT (handleWHMapButton()));
    connect(settingsButton, SIGNAL(clicked()), this, SLOT (handleSettingsButton()));
    connect(enterSingleButton, SIGNAL(clicked()), this, SLOT(handleSingleButton()));
}

ordermenu::~ordermenu()
{
    delete ui;
}

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
}

void ordermenu::onOtherSignal() {
    show();
}

void ordermenu::handleRouteButton() {
    this->hide();
    routeMap = new mainwhmap();
    connect (routeMap, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));

    routeMap->loadAllPoints(allPoints);
    routeMap->loadProductPoints(productPoints);
    routeMap->loadRoutePrinter(routePoints);
    routeMap->setFixedSize(1500, 1000);
    routeMap->setWindowTitle("Warehouse Map with Route");
    routeMap->show();
}

void ordermenu::handleWHMapButton() {

}

void ordermenu::handleSettingsButton() {

}

void ordermenu::handleSingleButton() {
    singleRoute.clear();
    Database *d = d->getInstance();
    std::string ID = txtwantsingle->text().toStdString();
    std::tuple<float, float> isReal = d->getProductPosition(ID);
    float x = std::get<0>(isReal);
    float y = std::get<1>(isReal);

    if (x == -1 || y == -1) {
        // Prompt user with an error message.
        QMessageBox notifyUser;
        notifyUser.setText("Please enter a valid ID!");
        notifyUser.setWindowTitle("Error!");
        notifyUser.exec();
    }

    else {
        this->hide();
        secWindow = new secondProductWindow();
        connect (secWindow, SIGNAL(fromOtherMenu()), this, SLOT(onOtherSignal()));

        secWindow->loadProductPoint(ID);
        singleRoute.push_back(routePoints[0]);

        std::cout << routePoints[routePoints.size() -2].x() << std::endl;
        std::cout << routePoints[routePoints.size() -2].y() << std::endl;

        singleRoute.push_back(routePoints[routePoints.size() -1]);
        secWindow->loadRoutePrinter(singleRoute);
        secWindow->loadInstructions();
        secWindow->setFixedSize(1500, 1000);
        secWindow->setWindowTitle("Single Product Map");
        secWindow->show();
    }
}
