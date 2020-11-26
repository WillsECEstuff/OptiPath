/*****************************************************************//**
 * @file   mainwhmap.cpp
 * @brief  This source file contains the definitions for mainwhmap.h
 * @date   October 2020
 *********************************************************************/
#include "mainwhmap.h"
#include "ui_mainwhmap.h"
#include <QPointF>
#include <QVector>
#include "Inventory.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <string>
#include <QWidget>
#include "WarehouseMap.h"

static const int TILE_SIZE = 30;
const int INKSCALE = 5;
const int MAPSCALE = 5;
const int xboundary = TILE_SIZE * 40; // max 40 length. Scaled by tilesize
const int yboundary = TILE_SIZE * 22;


mainwhmap::mainwhmap(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwhmap)
{
    //ui->setupUi(this);
    p_button = new QPushButton("Return to Order Menu", this);
    p_button->setGeometry(200,700,135,50);
    connect(p_button, SIGNAL (clicked()), this, SLOT (handleButton()));

    completeOrder_button = new QPushButton("Complete Order and Return", this);
    completeOrder_button->setGeometry(400, 700, 160, 50);
    connect(completeOrder_button, SIGNAL(clicked()), this, SLOT(handleCompleteOrderButton()));

    int instX = xboundary + 100; // x = 1300, location for instructions
    int instY = 280; // underneath the legend

    // create a scrollable instruction text area
    instrArea = new QScrollArea(parent=this);
    instrArea->setGeometry(instX - 25, instY + 15, 200, 300);
    instrArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    instrArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    instrArea->setWidgetResizable(true);
    dockArea = new QWidget();
    instrArea->setWidget(dockArea);
    instrList = new QVBoxLayout();
    dockArea->setLayout(instrList);

    height = 22;
    width = 40;
    flag = false;
}

mainwhmap::~mainwhmap()
{
    delete ui;
}

void mainwhmap::loadAllPoints(QVector <QPointF> ptsList) {
    // assumes points are already converted 
    allPoints = ptsList;
    std::cout << "loaded all" << std::endl;
}

void mainwhmap::loadUnconvertedPoints(QVector<QPointF> ptsList)
{
    for (auto& it : ptsList) {
        QPointF f(it.x() * TILE_SIZE / MAPSCALE, ((float)height - it.y()) * TILE_SIZE / MAPSCALE);
        allPoints.append(f);
    }
    std::cout << "coverted all points" << std::endl;
}

void mainwhmap::loadProductPoints(QVector <QPointF> ptsList) {
    // assumes points are already converted 
    productPoints = ptsList;
    std::cout << "loaded products" << std::endl;
}

void mainwhmap::loadUnconvertedProductPoints(QVector <QPointF> ptsList) {
    for (auto& it : ptsList) {
        QPointF f(it.x() * TILE_SIZE / MAPSCALE, ((float)height - it.y()) * TILE_SIZE / MAPSCALE);
        productPoints.append(f);
    }
    std::cout << "loaded converted product points" << std::endl;
}

void mainwhmap::loadRoutePrinter(QVector<QPointF> route) {
    routePoints = route;
    std::cout << "loaded route" << std::endl;
}

void mainwhmap::loadUnconvertedRoutePrinter(QVector<QPointF> route)
{
    for (auto& it : route) {
        QPointF f(it.x() * TILE_SIZE / MAPSCALE, ((float)height - it.y()) * TILE_SIZE / MAPSCALE);
        routePoints.append(f);
    }
    std::cout << "loaded route" << std::endl;
}

void mainwhmap::loadInstructions(QVector<std::string> instrs) {
    directions = instrs;
    std::cout << "loaded instructions" << std::endl;
    /*
    for (int i = 0; i < instrs.size(); i++) {
        QLabel *txtLblOrder = new QLabel(this);
        txtLblOrder->setText(QString::fromStdString(instrs[i]));
        instrList->addWidget(txtLblOrder);
        instrList->addSpacing(10);
    }
    instrArea->setLayout(instrList);
    instrArea->setWidgetResizable(true); */
}

void mainwhmap::loadOrderStatus(Order::Status stat)
{
    status = stat;
}

void mainwhmap::handleButton() {
    close();
    emit fromOtherMenu();
}

void mainwhmap::handleCompleteOrderButton() {
    close();
    emit COB();
}

void mainwhmap::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);
    QPen pen;
    

    //pen.setColor(Qt::green);
    pen.setWidth(5);

    // draw the whole map
    createGrid(&painter);
    drawOrderStatus(&painter);
    drawInstructions(&painter);
    drawLegend(&painter);
    drawShelves(&painter);
    drawContents(&painter);
    flag = true;

}

/**
 * @brief   A private function which draws the grid and labels
 * 
 * @param   painter
 */
void mainwhmap::createGrid(QPainter* painter) {

    // create and label grid begin. scaling coordinates by 30. Max product coordinate is 37.98 (*30 to scale)
    for (int i = 0; i < xboundary + 1; i += TILE_SIZE) {     // make a 40x22 map with 30 pixels per square
        painter->drawLine(i, 0, i, yboundary);
    }

    for (int j = 0; j < yboundary + 1; j += TILE_SIZE) {
        painter->drawLine(0, j, xboundary, j);
    }

    // label the 40x22 map
    // labeling the x axis
    for (int i = 0; i < xboundary - 1; i += TILE_SIZE * 5) {
        painter->drawText(i, yboundary + 15, QString::number(i / TILE_SIZE));
    }

    painter->drawText(xboundary - 5, yboundary + 15, QString::number(xboundary / TILE_SIZE)); // x = 40

    // labeling the y axis
    painter->drawText(xboundary + 5, 10, QString::number(height));
    for (int j = TILE_SIZE; j < yboundary + 1; j += TILE_SIZE) {
        int diff = height - (j / TILE_SIZE);
        if (diff % 5 == 0 && diff != 0) {
            painter->drawText(xboundary + 5, j + 4, QString::number(diff));
        }
    }
    // create and label grid end
}

/**
 * @brief   draws the products and routes in the grid
 * 
 * @param   painter
 */
void mainwhmap::drawContents(QPainter* painter)
{

    // draw map contents begin

    // draw product points
    painter->setPen(QPen(Qt::red, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));

    for (auto& it : allPoints) { // draw all points
        painter->drawPoint(it);
    }

    // draw products to be picked points
    painter->setPen(QPen(Qt::green, 10 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));

    for (auto& it : productPoints) { // draw product location
        painter->drawPoint(it);
    }


    // draw routes
    painter->setPen(QPen(Qt::cyan, 10 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->drawPoint(routePoints[0].x(), routePoints[0].y());
    painter->drawPoint(routePoints[routePoints.size() - 1].x(), routePoints[routePoints.size() - 1].y());

    painter->setPen(QPen(Qt::cyan, 1 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->setFont(QFont("times", 2));
    painter->drawText(routePoints[0].x() + 2, routePoints[0].y() + 3, "START");
    painter->drawText(routePoints[routePoints.size() - 1].x() + 2, routePoints[routePoints.size() - 1].y() - 3, "END");

    painter->setPen(QPen(Qt::blue, 1 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    for (int i = 1; i < routePoints.size() - 1; i++) {
        painter->drawLine(routePoints[i - 1].x(), routePoints[i - 1].y(), routePoints[i].x(), routePoints[i].y());
        painter->drawText(routePoints[i].x() + 2, routePoints[i].y() - 1, QString::number(i));
    }
    painter->drawLine(routePoints[routePoints.size() - 2].x(), routePoints[routePoints.size() - 2].y(), routePoints[routePoints.size() - 1].x(), routePoints[routePoints.size() - 1].y());
    // draw map contents end
}

/**
 * @brief   Draws the instructions inside the scrollable area
 * 
 * @param painter
 */
void mainwhmap::drawInstructions(QPainter* painter)
{
    int instX = xboundary + 100; // x = 1300, location for instructions
    int instY = 280; // underneath the legend

    // write instructions begin
    painter->drawText(instX + 40, instY, "Instructions");
    painter->drawText(instX - 25, instY + 5, "--------------------------------------------------");
    //for (int i = 0; i < directions.size(); i++) {
    //    std::string toBeNumbered = std::to_string(i + 1) + ". " + directions[i];
    //    QString temp = QString::fromStdString(toBeNumbered);
    //    painter->drawText(instX - 25, instY + 15 + i * 20, temp);
    //}
    // write instructions end

    if (!flag) {
        QLabel* orderLabel = new QLabel();
        std::string orderStr = "Instructions for Order";
        orderLabel->setText(QString::fromStdString(orderStr));
        instrList->addWidget(orderLabel);
        for (int i = 0; i < directions.size(); i++) {
            QLabel* txtLblOrder = new QLabel();
            std::string toBeNumbered = std::to_string(i + 1) + ". " + directions[i];
            txtLblOrder->setText(QString::fromStdString(toBeNumbered));
            instrList->addWidget(txtLblOrder);
        }
    }
    

}

/**
 * @brief   Draw the order status on the window
 * 
 * @param   painter
 */
void mainwhmap::drawOrderStatus(QPainter* painter)
{
    int odX = xboundary + 100; // x = 1300, location for order status
    int odY = 30; 

    painter->drawText(odX + 40, odY, "Order Status");
    painter->drawText(odX - 25, odY + 5, "-------------------------------------------");

    if (status == Order::Status::ORDER_EXECUTED) {
        painter->setPen(Qt::red);
        painter->drawText(odX - 25, odY + 20, "Order has been executed");
        painter->setPen(Qt::black);
    }
    else {
        painter->setPen(Qt::black);
        painter->drawText(odX - 25, odY + 20, "Order has NOT been executed");
        
    }
}

/**
 * @brief   Draws the legend for the map
 * 
 * @param   painter
 */
void mainwhmap::drawLegend(QPainter* painter)
{
    int legendX = xboundary + 100; // x = 1300, location for legend
    int legendY = 80;
    QColor orangeColor(255, 165, 0);

    // create legend begin
    painter->drawText(legendX + 40, legendY, "LEGEND");
    painter->drawText(legendX - 25, legendY + 5, "-------------------------------------------");
    painter->drawText(legendX + 25, legendY + 30, "Unselected Product");
    painter->drawText(legendX + 25, legendY + 60, "Selected Product");
    painter->drawText(legendX + 25, legendY + 90, "Route, numbered from");
    painter->drawText(legendX + 25, legendY + 100, "start->1->...->end");
    painter->drawText(legendX + 25, legendY + 130, "Start and End points");
    painter->drawText(legendX + 25, legendY + 160, "Shelf");

    painter->setPen(QPen(Qt::red, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->scale(MAPSCALE, MAPSCALE);
    painter->drawPoint(QPointF((legendX + 15) / MAPSCALE, (legendY + 25) / MAPSCALE));

    painter->setPen(QPen(Qt::green, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->drawPoint(QPointF((legendX + 15) / MAPSCALE, (legendY + 55) / MAPSCALE));

    painter->setPen(QPen(Qt::blue, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->drawLine((legendX + 5) / MAPSCALE, (legendY + 90) / MAPSCALE, (legendX + 15) / MAPSCALE, (legendY + 90) / MAPSCALE);

    painter->setPen(QPen(Qt::cyan, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->drawPoint(QPointF((legendX + 15) / MAPSCALE, (legendY + 125) / MAPSCALE));

    painter->setPen(QPen(orangeColor, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter->drawLine((legendX + 5) / MAPSCALE, (legendY + 155) / MAPSCALE, (legendX + 15) / MAPSCALE, (legendY + 155) / MAPSCALE);
    // create legend end
}

/**
 * @brief   Draw the shelves in the map
 * 
 * @param   painter
 */
void mainwhmap::drawShelves(QPainter* painter)
{
    WarehouseMap* whm = whm->getInstance();
    std::vector<std::tuple<int, int, int>> v = whm->getShelfSpecs(); // shelf num, begin, end
    QColor orangeColor(255, 165, 0);

    // draw shelves begin
    painter->setPen(QPen(orangeColor, 5 / (INKSCALE), Qt::SolidLine, Qt::RoundCap));
    QPointF beginPt, endPt;
    for (size_t i = 0; i < v.size(); i++) {
        int shelfNum = std::get<0>(v[i]); // y level
        int begin = std::get<1>(v[i]);
        int end = std::get<2>(v[i]) + 1;

        beginPt.setX(begin * TILE_SIZE / MAPSCALE);
        beginPt.setY((height - shelfNum) * TILE_SIZE / MAPSCALE);
        endPt.setX(end * TILE_SIZE / MAPSCALE);
        endPt.setY((height - shelfNum) * TILE_SIZE / MAPSCALE);
        painter->drawLine(beginPt.x(), beginPt.y(), endPt.x(), endPt.y());
    }
    // draw shelves end
}
