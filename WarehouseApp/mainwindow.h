#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QtWidgets>
#include "secondproductwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadAllPoints(QVector <QPointF> ptsList);
    void loadProductPoints(QVector <QPointF> ptsList);
    void loadRoutePrinter(QVector <QPointF> route);
    void loadInstructions(QVector <std::string> instrList);

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void handleButton();

private:
    Ui::MainWindow *ui;
    QVector <QPointF> allPoints;
    QVector <QPointF> productPoints;
    QVector <QPointF> routePoints;
    QVector <std::string> directions;
    QPushButton *p_button;
    QLineEdit *txtID;
    secondProductWindow *secWindow;
    QVector <QPointF> singleRoute;
};
#endif // MAINWINDOW_H
