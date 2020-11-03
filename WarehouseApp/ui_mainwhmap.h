/********************************************************************************
** Form generated from reading UI file 'mainwhmap.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWHMAP_H
#define UI_MAINWHMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwhmap
{
public:
    QWidget *centralwidget;
    QLineEdit *txtID;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainwhmap)
    {
        if (mainwhmap->objectName().isEmpty())
            mainwhmap->setObjectName(QString::fromUtf8("mainwhmap"));
        mainwhmap->resize(1223, 964);
        centralwidget = new QWidget(mainwhmap);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txtID = new QLineEdit(centralwidget);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(200, 750, 50, 25));
        mainwhmap->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainwhmap);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1223, 21));
        mainwhmap->setMenuBar(menubar);
        statusbar = new QStatusBar(mainwhmap);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mainwhmap->setStatusBar(statusbar);

        retranslateUi(mainwhmap);

        QMetaObject::connectSlotsByName(mainwhmap);
    } // setupUi

    void retranslateUi(QMainWindow *mainwhmap)
    {
        mainwhmap->setWindowTitle(QCoreApplication::translate("mainwhmap", "mainwhmap", nullptr));
        txtID->setPlaceholderText(QCoreApplication::translate("mainwhmap", "123", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwhmap: public Ui_mainwhmap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWHMAP_H
