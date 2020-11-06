/********************************************************************************
** Form generated from reading UI file 'ordermenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMENU_H
#define UI_ORDERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ordermenu
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ordermenu)
    {
        if (ordermenu->objectName().isEmpty())
            ordermenu->setObjectName(QString::fromUtf8("ordermenu"));
        ordermenu->resize(800, 600);
        centralwidget = new QWidget(ordermenu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ordermenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ordermenu);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ordermenu->setMenuBar(menubar);
        statusbar = new QStatusBar(ordermenu);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ordermenu->setStatusBar(statusbar);

        retranslateUi(ordermenu);

        QMetaObject::connectSlotsByName(ordermenu);
    } // setupUi

    void retranslateUi(QMainWindow *ordermenu)
    {
        ordermenu->setWindowTitle(QCoreApplication::translate("ordermenu", "ordermenu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ordermenu: public Ui_ordermenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMENU_H
