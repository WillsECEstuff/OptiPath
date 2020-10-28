#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPointF>
#include <QVector>
#include "Inventory.h"
#include <iostream>
#include <QDebug>
#include <QString>

static const int TILE_SIZE = 30;
const int INKSCALE = 5;
const int MAPSCALE = 5;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::cout << "created" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAllPoints(QVector <QPointF> ptsList) {
    allPoints = ptsList;
    std::cout << "loaded all" << std::endl;
}

void MainWindow::loadProductPoints(QVector <QPointF> ptsList) {
    productPoints = ptsList;
    std::cout << productPoints.size() << std::endl;
    std::cout << "loaded products" << std::endl;
}

void MainWindow::loadRoutePrinter(QVector<QPointF> route) {
    routePoints = route;
    std::cout << routePoints.size() << std::endl;
    std::cout << "loaded route" << std::endl;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);
    QPen pen;

    qDebug() << "test";

    //points = readDB(); // read the database (TEMPORARY)

    int xboundary = TILE_SIZE * 40; // max 40 length? Scaled by tilesize
    int yboundary = TILE_SIZE * 22;

    pen.setColor(Qt::green);
    pen.setWidth(5);

    // draw stuff. scaling coordinates by 30. Max product coordinate is 37.98 (*30 to scale)

    for (int i = 0; i < xboundary+1; i += TILE_SIZE) { // make a 40x40 map with 30 pixels per square
        painter.drawLine(i, 0, i, yboundary);
    }

    for (int j = 0; j < yboundary+1; j += TILE_SIZE) {
        painter.drawLine(0, j, xboundary, j);
    }

    //painter.drawPoint(2.5*tileSize/scale, 5*tileSize/scale); // test point

    /* Fill in points with n number of points
    for(int i = 0; i < yboundary; i++) {
        allPoints.append(QPointF(i*TILE_SIZE/SCALE, i*TILE_SIZE/SCALE));
    } */

    qDebug() << allPoints.size();
    qDebug() << productPoints.size();

    painter.setPen(QPen(Qt::red, 5/(INKSCALE), Qt::SolidLine, Qt::RoundCap));
    painter.scale(MAPSCALE, MAPSCALE);

    for (auto& it : allPoints) { // draw all points
        painter.drawPoint(it);
    }

    painter.setPen(QPen(Qt::green, 10/(INKSCALE), Qt::SolidLine, Qt::RoundCap));

    for (auto& it : productPoints) { // draw product location
        painter.drawPoint(it);
    }

    painter.setPen(QPen(Qt::blue, 1/(INKSCALE), Qt::SolidLine, Qt::RoundCap));

    for (int i = 0; i < routePoints.size() - 1; i++) {
        painter.drawLine(routePoints[i].x(), routePoints[i].y(), routePoints[i+1].x(), routePoints[i+1].y());
        painter.drawText(routePoints[i].x()+5, routePoints[i].y(), QString::number(i));

        if (i == routePoints.size() - 1) {
            painter.drawText(routePoints[i+1].x(), routePoints[i+1].y(), QString::number(i+1));
        }
    }

}
