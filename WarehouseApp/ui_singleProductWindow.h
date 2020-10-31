/********************************************************************************
** Form generated from reading UI file 'singleProductWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_singleProductWindow_H
#define UI_singleProductWindow_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QsingleProductWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_singleProductWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(singleProductWindow *singleProductWindow)
    {
        if (singleProductWindow->objectName().isEmpty())
            singleProductWindow->setObjectName(QString::fromUtf8("singleProductWindow"));
        singleProductWindow->resize(800, 600);
        centralwidget = new QWidget(singleProductWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        singleProductWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(singleProductWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        singleProductWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(singleProductWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        singleProductWindow->setStatusBar(statusbar);

        retranslateUi(singleProductWindow);

        QMetaObject::connectSlotsByName(singleProductWindow);
    } // setupUi

    void retranslateUi(QsingleProductWindow *singleProductWindow)
    {
        singleProductWindow->setWindowTitle(QCoreApplication::translate("singleProductWindow", "singleProductWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class singleProductWindow: public Ui_singleProductWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEPRODUCTWINDOW_H
