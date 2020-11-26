/********************************************************************************
** Form generated from reading UI file 'settingsmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSMENU_H
#define UI_SETTINGSMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingsmenu
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *settingsmenu)
    {
        if (settingsmenu->objectName().isEmpty())
            settingsmenu->setObjectName(QString::fromUtf8("settingsmenu"));
        settingsmenu->resize(800, 600);
        centralwidget = new QWidget(settingsmenu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        settingsmenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(settingsmenu);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        settingsmenu->setMenuBar(menubar);
        statusbar = new QStatusBar(settingsmenu);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        settingsmenu->setStatusBar(statusbar);

        retranslateUi(settingsmenu);

        QMetaObject::connectSlotsByName(settingsmenu);
    } // setupUi

    void retranslateUi(QMainWindow *settingsmenu)
    {
        settingsmenu->setWindowTitle(QCoreApplication::translate("settingsmenu", "settingsmenu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingsmenu: public Ui_settingsmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSMENU_H
