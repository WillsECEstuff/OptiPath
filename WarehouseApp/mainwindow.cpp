#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPointF>
#include <QVector>

static const int TILE_SIZE = 15;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);
    QPen pen;
    QVector <QPointF> points;

    int tileSize = TILE_SIZE;
    int scale = 5; // only for making points
    int boundary = tileSize * 40; // max 40 length? Scaled by tilesize

    pen.setColor(Qt::green);
    pen.setWidth(5);

    // draw stuff. scaling coordinates by 30. Max product coordinate is 37.98 (*30 to scale)

    for (int i = 0; i < boundary+1; i += tileSize) { // make a 40x40 map with 30 pixels per square
        painter.drawLine(i, 0, i, boundary);
    }

    for (int j = 0; j < boundary+1; j += tileSize) {
        painter.drawLine(0, j, boundary, j);
    }

    painter.setPen(QPen(Qt::red, 5/(scale), Qt::SolidLine, Qt::RoundCap));
    painter.scale(scale, scale);
    //painter.drawPoint(2.5*tileSize/scale, 5*tileSize/scale); // test point

    // Fill in points with n number of points
    for(int i = 0; i < boundary; i++) {
        points.append(QPointF(i*tileSize/scale, i*tileSize/scale));
    }

    for (int i = 0; i < points.size(); i++) {
        painter.drawPoint(points[i]);
    }
}
