/*****************************************************************//**
 * @file   secondproductwindow.cpp
 * @brief  This source file contains the definition for secondproductwindow.h
 * @date   October 2020
 *********************************************************************/
#include "secondproductwindow.h"
#include "ui_secondproductwindow.h"
#include <QPointF>
#include <QVector>
#include "Inventory.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <string>
#include "Database.h"
#include "mainwhmap.h"
#include "WarehouseMap.h"

static const int TILE_SIZE = 30;
const int INKSCALE = 5;
const int MAPSCALE = 5;


secondProductWindow::secondProductWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::secondProductWindow)
{
    returnButton = new QPushButton("Return to Order Menu", this);
    returnButton->setGeometry(200,700,135,50);
    connect(returnButton, SIGNAL (clicked()), this, SLOT (handleButton()));

    height = 22;
    width = 40;
}

secondProductWindow::~secondProductWindow()
{
    delete ui;
}

void secondProductWindow::loadProductPoint(std::string pID) {
    productPoint.setX(0);
    productPoint.setY(0);
    myPID = pID;
    Database *d = d->getInstance();
    std::tuple<float, float> t = d->getProductPosition(myPID);
    float x = std::get<0>(t);
    float y = std::get<1>(t);

    if (x < 0 || y < 0) {
        close();
    }

    productPoint.setX(x * TILE_SIZE/MAPSCALE);
    productPoint.setY( ( (float) height - y) * TILE_SIZE/MAPSCALE);
    isPreview = false;
    std::cout << "loaded product" << std::endl;
}

void secondProductWindow::loadAllPoints(QVector <QPointF> ptsList) {
    allPoints = ptsList;
    std::cout << "loaded all" << std::endl;
}

void secondProductWindow::loadUnconvertedPoints(QVector<QPointF> ptsList)
{
    for (auto& it : ptsList) {
        QPointF f(it.x() * TILE_SIZE / MAPSCALE, ((float)height - it.y()) * TILE_SIZE / MAPSCALE);
        allPoints.append(f);
    }

    std::cout << "coverted all points" << std::endl;
}

void secondProductWindow::loadRoutePrinter(QVector<QPointF> route) {
    routePoints = route;
    std::cout << "loaded route" << std::endl;
}

void secondProductWindow::loadUnconvertedRoutePrinter(QVector<QPointF> route)
{
    for (auto& it : route) {
        QPointF f(it.x() * TILE_SIZE / MAPSCALE, ((float)height - it.y()) * TILE_SIZE / MAPSCALE);
        routePoints.append(f);
    }
    std::cout << "loaded route" << std::endl;
}

void secondProductWindow::loadInstructions(QVector <std::string> instrList) {
    directions = instrList;
    std::cout << "loaded instructions" << std::endl;
}

void secondProductWindow::handleButton() {
    close();
    emit fromOtherMenu();
}

void secondProductWindow::setPreview(bool b) {
    isPreview = b;
}

void secondProductWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.eraseRect(0,0,1500,1000);
    painter.setBrush(Qt::DiagCrossPattern);
    QPen pen;
    QColor orangeColor(255,165,0); // custom orange color for shelves

    int xboundary = TILE_SIZE * 40; // max 40 length
    int yboundary = TILE_SIZE * 22;
    int legendX = xboundary + 100; // x = 1300, location for legend
    WarehouseMap* whm = whm->getInstance();
    std::vector<std::tuple<int, int, int>> v = whm->getShelfSpecs(); // shelf num, begin, end

    //pen.setColor(Qt::green);
    pen.setWidth(5);

    // create and label grid
    createGrid(&painter);

    if (isPreview == false) {
        // write instructions begin
        painter.drawText(xboundary/2 + 40, yboundary + 40, "Instructions");
        painter.drawText(xboundary/2 - 25, yboundary + 45, "--------------------------------------------------");
        for (int i = 0; i < directions.size(); i++) {
            std::string toBeNumbered = std::to_string(i+1) + ". " + directions[i];
            QString temp = QString::fromStdString(toBeNumbered);
            painter.drawText(xboundary/2 - 25, yboundary + 60 + i*20, temp);
        }
        // write instructions end

        // create legend begin, for single product map
        painter.drawText(legendX + 40, 30, "LEGEND");
        painter.drawText(legendX - 25, 35, "-------------------------------------------");
        painter.drawText(legendX + 25, 60, "Unselected Product");
        painter.drawText(legendX + 25, 90, "Selected Product");
        painter.drawText(legendX + 25, 120, "Route, numbered from");
        painter.drawText(legendX + 25, 130, "start->1->...->end");
        painter.drawText(legendX + 25, 150, "Start and End points");
        painter.drawText(legendX + 25, 180, "Shelf");

        painter.setPen(QPen(Qt::red, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.scale(MAPSCALE, MAPSCALE);
        painter.drawPoint(QPointF((legendX + 15) / MAPSCALE, 60 / MAPSCALE));

        painter.setPen(QPen(Qt::green, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF((legendX + 15) / MAPSCALE, 90 / MAPSCALE));

        painter.setPen(QPen(Qt::blue, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawLine((legendX + 5) / MAPSCALE, 120 / MAPSCALE, (legendX + 15) / MAPSCALE, 120 / MAPSCALE);

        painter.setPen(QPen(Qt::cyan, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF((legendX + 15) / MAPSCALE, 150 / MAPSCALE));

        painter.setPen(QPen(orangeColor, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawLine((legendX + 5) / MAPSCALE, 180 / MAPSCALE, (legendX + 15) / MAPSCALE, 180 / MAPSCALE);
        // create legend end
    }

    else {
        // create legend begin, for preview only
        painter.drawText(legendX + 40, 30, "LEGEND");
        painter.drawText(legendX - 25, 35, "-------------------------------------------");
        painter.drawText(legendX + 25, 60, "Unselected Product");
        painter.drawText(legendX + 25, 90, "Start and End points");
        painter.drawText(legendX + 25, 120, "Shelf");

        painter.setPen(QPen(Qt::red, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.scale(MAPSCALE, MAPSCALE);
        painter.drawPoint(QPointF((legendX + 15) / MAPSCALE, 60 / MAPSCALE));

        painter.setPen(QPen(Qt::cyan, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF((legendX + 15) / MAPSCALE, 90 / MAPSCALE));

        painter.setPen(QPen(orangeColor, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawLine((legendX + 5) / MAPSCALE, 120 / MAPSCALE, (legendX + 15) / MAPSCALE, 120 / MAPSCALE);
    }
    // create legend end

    // draw shelves
    drawShelves(&painter);

    // draw map contents begin
    painter.setPen(QPen(Qt::red, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));

    for (auto& it : allPoints) { // draw all points
        painter.drawPoint(it);
    }

    if (isPreview == false) { // draw the single product point, only if not in preview mode
        painter.setPen(QPen(Qt::green, 10/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(productPoint);
    }

    painter.setPen(QPen(Qt::cyan, 10/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(routePoints[0].x(), routePoints[0].y());
    //painter.drawPoint(routePoints[routePoints.size() - 1].x(), routePoints[routePoints.size() - 1].y());

    painter.setPen(QPen(Qt::cyan, 1/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter.setFont(QFont("times",2));
    painter.drawText(routePoints[0].x()+2, routePoints[0].y()+3, "START");
    painter.drawText(routePoints[routePoints.size() - 1].x()+2, routePoints[routePoints.size() - 1].y()-3, "END");

    if (isPreview == false) { // draw route. used only for product map
        painter.setPen(QPen(Qt::blue, 1/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
        for (int i = 1; i < routePoints.size(); i++) {
            painter.drawLine(routePoints[i-1].x(), routePoints[i-1].y(), routePoints[i].x(), routePoints[i].y());
            painter.drawText(routePoints[i].x()+2, routePoints[i].y()+4, QString::number(i));
        }
        //painter.drawLine(routePoints[routePoints.size() - 1].x(), routePoints[routePoints.size() - 1].y(), routePoints[routePoints.size() - 1].x(), routePoints[routePoints.size() - 1].y());
    }
    // draw map contents end
}


void secondProductWindow::createGrid(QPainter* painter)
{
    int xboundary = TILE_SIZE * 40; // max 40 length
    int yboundary = TILE_SIZE * 22;

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

void secondProductWindow::drawShelves(QPainter* painter)
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