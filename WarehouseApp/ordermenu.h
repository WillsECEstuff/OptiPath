#ifndef ORDERMENU_H
#define ORDERMENU_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QtWidgets>
#include "mainwhmap.h"
#include "secondproductwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ordermenu; }
QT_END_NAMESPACE

class ordermenu : public QMainWindow
{
    Q_OBJECT

public:
    ordermenu(QWidget *parent = nullptr);
    ~ordermenu();

    void loadAllPoints(QVector <QPointF> ptsList);
    void loadProductPoints(QVector <QPointF> ptsList);
    void loadRoutePrinter(QVector <QPointF> route);
    void loadInstructions(QVector <std::string> instrList);

public slots:
    void onOtherSignal();

private slots:
    void handleRouteButton();
    void handleWHMapButton();
    void handleSettingsButton();
    void handleSingleButton();

private:
    Ui::ordermenu *ui;

    QVector <QPointF> allPoints;
    QVector <QPointF> productPoints;
    QVector <QPointF> routePoints;
    QVector <std::string> directions;

    QPushButton *allWHMapButton;
    QPushButton *routeButton;
    QPushButton *enterSingleButton;
    QPushButton *settingsButton;
    QLabel *txtOrder;
    QFont *font;
    QComboBox *ordercbox;
    QLineEdit *txtwantsingle;
    QLabel *txtLbl;

    mainwhmap *routeMap;
    secondProductWindow *secWindow;
    QVector <QPointF> singleRoute;
};
#endif // ORDERMENU_H
