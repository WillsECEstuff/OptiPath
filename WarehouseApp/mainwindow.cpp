#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPointF>
#include <QVector>
#include "Database.h"
#include <QDebug>

static const int TILE_SIZE = 15;
const int SCALE = 5;
QVector <QPointF> points;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //points = readDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
QVector <QPointF> MainWindow::readDB() {
    //Database *d = d->getInstance();
    //d->deleteDatabase();
    //d->populateDatabase("qvBox-warehouse-data-f20-v01.txt");
    //std::vector<std::tuple<float, float>> locList = d->getLocList();
    QVector <QPointF> listPoints;
    int c = 1;
    qDebug() << "before";

    std::tuple<float, float> t = d->getProductPosition("1");
    qDebug() << std::get<0>(t) << " " << std::get<1>(t) << endl;

    for (std::tuple<float,float> item: locList) { // bugged currently
        float x = std::get<0>(item);
        float y = std::get<1>(item);
        qDebug() << x;
        qDebug() << y;
        listPoints.append(QPointF(x*TILE_SIZE/SCALE, y*TILE_SIZE/SCALE));
        qDebug() << "Item #" << c << ": " << x << " " << y << endl; // test only. WARNING: VERY LONG!
        c++;
    }
    qDebug() << "after";
    return listPoints;
} */

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);
    QPen pen;

    qDebug() << "test";

    //points = readDB(); // read the database (TEMPORARY)

    //int tileSize = TILE_SIZE;
    //int scale = 5; // only for making points
    int boundary = TILE_SIZE * 40; // max 40 length? Scaled by tilesize

    pen.setColor(Qt::green);
    pen.setWidth(5);

    // draw stuff. scaling coordinates by 30. Max product coordinate is 37.98 (*30 to scale)

    for (int i = 0; i < boundary+1; i += TILE_SIZE) { // make a 40x40 map with 30 pixels per square
        painter.drawLine(i, 0, i, boundary);
    }

    for (int j = 0; j < boundary+1; j += TILE_SIZE) {
        painter.drawLine(0, j, boundary, j);
    }

    painter.setPen(QPen(Qt::red, 5/(SCALE), Qt::SolidLine, Qt::RoundCap));
    painter.scale(SCALE, SCALE);
    //painter.drawPoint(2.5*tileSize/scale, 5*tileSize/scale); // test point

    // Fill in points with n number of points
    for(int i = 0; i < boundary; i++) {
        points.append(QPointF(i*TILE_SIZE/SCALE, i*TILE_SIZE/SCALE));
    }

    for (int i = 0; i < points.size(); i++) {
        painter.drawPoint(points[i]);
    }
}
