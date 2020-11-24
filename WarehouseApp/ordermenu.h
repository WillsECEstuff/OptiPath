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

private slots:
    void handleRouteButton();
    void handleSLocationButton();
    void handleELocationButton();
    void handleCreateOrderButton();
    void handleSingleButton();
    void handleTimerButton();

private:
    Ui::ordermenu *ui;
    float myTimer;
    QVector <QPointF> allPoints;
    QVector <QPointF> productPoints;
    QVector <QPointF> routePoints;
    QVector <std::string> directions;
    //QVector <std::string> prodIDs;
    QVector <Order> orderList;
    std::tuple<float, float> startLocation;
    std::tuple<float, float> endLocation;

    QPushButton *startLocationButton;
    QPushButton *endLocationButton;
    QPushButton *routeButton;
    QPushButton *enterSingleButton;
    QPushButton *addOrderButton;
    QPushButton *settingsButton;
    QPushButton *timerButton;
    QLabel *txtOrder;
    QFont *font;
    QComboBox *ordercbox;
    QLineEdit *txtwantsingle;
    QLabel *txtLblSingle;
    QLineEdit *txtSLoc;
    QLabel *txtLblSLoc;
    QLineEdit *txtELoc;
    QLabel *txtLblELoc;
    QLineEdit *txtAddOrder;
    QLabel *txtLblOrder;
    QLineEdit *txtTimer;
    QLabel *txtLblTimer;

    mainwhmap *routeMap;
    secondProductWindow *secWindow;
    QVector <QPointF> singleRoute;
};
#endif // ORDERMENU_H
