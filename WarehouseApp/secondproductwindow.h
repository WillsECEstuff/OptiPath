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
    void loadInstructions();
    void loadAllPoints(QVector <QPointF> ptsList);

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
};
#endif // SECONDPRODUCTWINDOW_H
