/********************************************************************************
** Form generated from reading UI file 'mainwhmap.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_mainwhmap_H
#define UI_mainwhmap_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/Qmainwhmap>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwhmap
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(Qmainwhmap *mainwhmap)
    {
        if (mainwhmap->objectName().isEmpty())
            mainwhmap->setObjectName(QString::fromUtf8("mainwhmap"));
        mainwhmap->resize(800, 600);
        centralwidget = new QWidget(mainwhmap);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainwhmap->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainwhmap);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        mainwhmap->setMenuBar(menubar);
        statusbar = new QStatusBar(mainwhmap);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mainwhmap->setStatusBar(statusbar);

        retranslateUi(mainwhmap);

        QMetaObject::connectSlotsByName(mainwhmap);
    } // setupUi

    void retranslateUi(Qmainwhmap *mainwhmap)
    {
        mainwhmap->setWindowTitle(QCoreApplication::translate("mainwhmap", "mainwhmap", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwhmap: public Ui_mainwhmap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_mainwhmap_H
