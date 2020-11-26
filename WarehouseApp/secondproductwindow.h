/*******************************************************************
 * @file   secondProductWindow.h
 * @brief  This header includes the secondProductWindow class.
 * @date   October 2020
 *********************************************************************/
#ifndef SECONDPRODUCTWINDOW_H
#define SECONDPRODUCTWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class secondProductWindow; }
QT_END_NAMESPACE

class secondProductWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondProductWindow(QWidget *parent = 0);
    ~secondProductWindow();

    void loadProductPoint(std::string pt);
    void loadRoutePrinter(QVector <QPointF> route);
    void loadUnconvertedRoutePrinter(QVector <QPointF> route);
    void loadInstructions(QVector <std::string> instrList);
    void loadAllPoints(QVector <QPointF> ptsList);
    void loadUnconvertedPoints(QVector <QPointF> ptsList);
    void setPreview(bool b);
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void handleButton();

signals:
    void fromOtherMenu();

private:
    Ui::secondProductWindow *ui;
    std::string myPID;
    QPoint productPoint;
    QVector <QPointF> allPoints;
    QVector <QPointF> routePoints;
    QVector <std::string> directions;
    QPushButton *returnButton;
    bool isPreview;

    int width;
    int height;

    void createGrid(QPainter* painter);
    void drawShelves(QPainter* painter);
};
#endif // SECONDPRODUCTWINDOW_H
