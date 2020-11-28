/*******************************************************************
 * @file   ordermenu.h
 * @brief  This header includes the ordermenu class.
 * @date   October 2020
 *********************************************************************/
#ifndef ORDERMENU_H
#define ORDERMENU_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QtWidgets>
#include "mainwhmap.h"
#include "secondproductwindow.h"
#include "settingsmenu.h"
#include "Ticket.h"
#include "Order.h"
#include "PathFinder.h"
#include "Database.h"
#include "OrderHelper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ordermenu; }
QT_END_NAMESPACE

class ordermenu : public QMainWindow
{
    Q_OBJECT

public:
    ordermenu(QWidget *parent = nullptr);
    ~ordermenu();

    void processOrder(Order* o, Database* d, int oIdx);

public slots:
    void onOtherSignal();
    void onOrderCompleteSignal();
    void onSettingsSignal();

private slots:
    void handleRouteButton();
    void handleCreateOrderButton();
    void handleSingleButton();
    void handleSettingsButton();

private:
    Ui::ordermenu *ui;
    float myTimer = 60.0;
    QVector <QPointF> allPoints;
    QVector <QPointF> productPoints;
    QVector <QPointF> routePoints;
    QVector <std::string> directions;
    QVector <Order> orderList;
    std::tuple<float, float> startLocation;
    std::tuple<float, float> endLocation;

    QPushButton *routeButton;
    QPushButton *enterSingleButton;
    QPushButton *addOrderButton;
    QPushButton *settingsButton;
    QLabel *txtOrder;
    QFont *font;
    QComboBox *ordercbox;
    QLineEdit *txtwantsingle;
    QLabel *txtLblSingle;
    QLineEdit *txtAddOrder;
    QLabel *txtLblOrder;

    mainwhmap *routeMap;
    secondProductWindow *secWindow;
    settingsmenu *settingsWindow;
    QVector <QPointF> singleRoute;

    int currentOrderIDx;
};
#endif // ORDERMENU_H
