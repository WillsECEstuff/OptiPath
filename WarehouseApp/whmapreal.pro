QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Inventory.cpp \
    MST.cpp \
    OrderHelper.cpp \
    WarehouseApp.cpp \
    WarehouseMap.cpp \
    AdjacencyMatrix.cpp \
    Database.cpp \
    Order.cpp \
    ordermenu.cpp \
    PathFinder.cpp \
    PriorityQueue.cpp \
    Product.cpp \
    mainwhmap.cpp \
    secondproductwindow.cpp \
    Ticket.cpp

HEADERS += \
    Inventory.h \
    MST.h \
    OrderHelper.h \
    WarehouseMap.h \
    AdjacencyMatrix.h \
    Database.h \
    Order.h \
    ordermenu.h \
    PathFinder.h \
    PriorityQueue.h \
    Product.h \
    mainwhmap.h \
    secondproductwindow.h \
    Ticket.h \
    ui_mainwhmap.h \
    ui_singleProductWindow.h

FORMS += \
    mainwhmap.ui \
    ordermenu.ui \
    secondproductwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ClassDiagram.cd \
    qvBox-warehouse-data-f20-v01.txt
