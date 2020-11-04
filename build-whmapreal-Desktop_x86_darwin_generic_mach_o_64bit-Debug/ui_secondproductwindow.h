/********************************************************************************
** Form generated from reading UI file 'secondproductwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDPRODUCTWINDOW_H
#define UI_SECONDPRODUCTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_secondProductWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *secondProductWindow)
    {
        if (secondProductWindow->objectName().isEmpty())
            secondProductWindow->setObjectName(QString::fromUtf8("secondProductWindow"));
        secondProductWindow->resize(800, 600);
        centralwidget = new QWidget(secondProductWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        secondProductWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(secondProductWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        secondProductWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(secondProductWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        secondProductWindow->setStatusBar(statusbar);

        retranslateUi(secondProductWindow);

        QMetaObject::connectSlotsByName(secondProductWindow);
    } // setupUi

    void retranslateUi(QMainWindow *secondProductWindow)
    {
        secondProductWindow->setWindowTitle(QCoreApplication::translate("secondProductWindow", "secondProductWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class secondProductWindow: public Ui_secondProductWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDPRODUCTWINDOW_H
