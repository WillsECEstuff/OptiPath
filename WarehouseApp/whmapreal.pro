QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Inventory.cpp \
    WarehouseApp.cpp \
    mainwindow.cpp \
    AdjacencyMatrix.cpp \
    Database.cpp \
    Order.cpp \
    PathFinder.cpp \
    PriorityQueue.cpp \
    Product.cpp \
    Ticket.cpp \

HEADERS += \
    Inventory.h \
    mainwindow.h \
    AdjacencyMatrix.h \
    Database.h \
    Order.h \
    PathFinder.h \
    PriorityQueue.h \
    Product.h \
    Ticket.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qvBox-warehouse-data-f20-v01.txt
