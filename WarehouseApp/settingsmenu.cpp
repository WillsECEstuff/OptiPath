#include "settingsmenu.h"
#include "ui_settingsmenu.h"
#include <QPointF>
#include <QVector>
#include <iostream>
#include <QDebug>
#include <QString>
#include <string>
#include <iomanip>
#include <sstream>
#include "ordermenu.h"

settingsmenu::settingsmenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::settingsmenu)
{
    ui->setupUi(this);
    std::cout << "timer: " << myTimer << std::endl;
    std::cout << "starting x: " << std::get<0>(mySLocation) << std::endl;

    startLocationButton = new QPushButton("Change Starting Location", this);
    startLocationButton->setGeometry(100,200,135,50);
    endLocationButton = new QPushButton("Change Ending Location", this);
    endLocationButton->setGeometry(345,200,135,50);
    timerButton = new QPushButton("Change Timer", this);
    timerButton->setGeometry(235,360,110,50);
    applyButton = new QPushButton("Apply Settings", this);
    applyButton->setGeometry(340,550,135,50);
    returnButton = new QPushButton("Quit without saving", this);
    returnButton->setGeometry(100,550,135,50);

    txtSettings = new QLabel(this);
    QFont font = txtSettings->font();
    font.setPointSize(25);
    txtSettings->setText("Settings");
    txtSettings->setFont(font);
    txtSettings->setGeometry(225,80,125,50);

    txtLblSLoc = new QLabel(this);
    txtLblSLoc->setText("Enter a location below\nas (x,y) without parentheses,\nthen click on\n'Change Starting Location.'");
    txtLblSLoc->setGeometry(100,260,300,60);
    txtSLoc = new QLineEdit(this);
    txtSLoc->setPlaceholderText("0,0");
    txtSLoc->setGeometry(145,325,50,25);

    txtLblELoc = new QLabel(this);
    txtLblELoc->setText("Enter a location below\nas (x,y) without parentheses,\nthen click on\n'Change Ending Location.'");
    txtLblELoc->setGeometry(345,260,300,60);
    txtELoc = new QLineEdit(this);
    txtELoc->setPlaceholderText("0,0");
    txtELoc->setGeometry(390,325,50,25);

    txtLblTimer = new QLabel(this);
    txtLblTimer->setText("Change the timer below,\nin seconds. Warning: timer\n should be longer than 5 seconds.");
    txtLblTimer->setGeometry(235,420,300,40);
    txtTimer = new QLineEdit(this);
    txtTimer->setPlaceholderText("60.0");
    txtTimer->setGeometry(265,475,50,25);

    connect(startLocationButton, SIGNAL (clicked()), this, SLOT (handleSLocationButton()));
    connect(endLocationButton, SIGNAL (clicked()), this, SLOT (handleELocationButton()));
    connect(timerButton, SIGNAL(clicked()), this, SLOT(handleTimerButton()));
    connect(returnButton, SIGNAL (clicked()), this, SLOT (handleReturnButton()));
    connect(applyButton, SIGNAL (clicked()), this, SLOT (handleApplyButton()));
}

settingsmenu::~settingsmenu()
{
    delete ui;
}

void settingsmenu::setTextFields() {
    std::string txtS, txtE, txtT = "";
    std::stringstream sxS, syS, sxE, syE, sT;
    float xS = std::get<0>(mySLocation);
    float yS = std::get<1>(mySLocation);
    float xE = std::get<0>(myELocation);
    float yE = std::get<1>(myELocation);
    float tempTimer = myTimer;
    std::cout << "temptimer: " << tempTimer << std::endl;

    sxS << std::fixed << std::setprecision(1) << xS;
    syS << std::fixed << std::setprecision(1) << yS;
    sxE << std::fixed << std::setprecision(1) << xE;
    syE << std::fixed << std::setprecision(1) << yE;
    sT << std::fixed << std::setprecision(1) << tempTimer;


    txtS = sxS.str() + "," + syS.str();
    txtE = sxE.str() + "," + syE.str();
    txtT = sT.str();

    txtSLoc->setText(QString::fromStdString(txtS));
    txtELoc->setText(QString::fromStdString(txtE));
    txtTimer->setText(QString::fromStdString(txtT));
}

void settingsmenu::handleReturnButton() {
    close();
    emit fromOtherMenu();
}

void settingsmenu::handleApplyButton() {
    emit fromSettingsMenu();
}

void settingsmenu::handleSLocationButton() {
    std::string sLoc = txtSLoc->text().toStdString();
    int idx = (int)sLoc.find(",");
    std::string xLoc = sLoc.substr(0, idx);
    std::string yLoc = sLoc.substr(idx+1);
    std::string notify = "Please enter a valid location (0 <= X <= 40, 0 <= Y <= 22). Y must be odd; even Y is a shelf.";

    float x = 0, y = 0;

    if (isdigit(xLoc[0]) == 0 || isdigit(yLoc[0]) == 0) { // not a number
        QMessageBox notifyUser;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Error - Entered Location");
        notifyUser.exec();
    }

    else {
        x = stof(xLoc);
        y = stof(yLoc);

        int ycheck = (int)y;

        if (x < 0 || x > 40 || y < 0 || y > 22 || idx == -1 || ycheck % 2 == 0) { // out of bounds/invalid
            QMessageBox notifyUser;
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Error - Entered Location");
            notifyUser.exec();
        }

        else {
            std::get<0>(mySLocation) = x;
            std::get<1>(mySLocation) = y;

            std::cout << "Start X = " << std::get<0>(mySLocation) << ", start Y = " << std::get<1>(mySLocation) << std::endl;

            QMessageBox notifyUser;
            std::string notify = "Location entered successfully. X = " + std::to_string(std::get<0> (mySLocation)) + ", Y = " + std::to_string(std::get<1> (mySLocation));
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Success - Entered Location");
            notifyUser.exec();
        }
    }
}

void settingsmenu::handleELocationButton() {
    std::string eLoc = txtELoc->text().toStdString();
    int idx = (int)eLoc.find(",");
    std::string xLoc = eLoc.substr(0, idx);
    std::string yLoc = eLoc.substr(idx+1);
    std::string notify = "Please enter a valid location (0 <= X <= 40, 0 <= Y <= 22). Y must be odd; even Y is a shelf.";

    float x = 0, y = 0;

    if (isdigit(xLoc[0]) == 0 || isdigit(yLoc[0]) == 0) { // not a number
        QMessageBox notifyUser;
        notifyUser.setText(QString::fromStdString(notify));
        notifyUser.setWindowTitle("Error - Entered Location");
        notifyUser.exec();
    }

    else {
        x = stof(xLoc);
        y = stof(yLoc);

        int ycheck = (int)y;

        if (x < 0 || x > 40 || y < 0 || y > 22 || idx == -1 || ycheck % 2 == 0) { // out of bounds/invalid
            QMessageBox notifyUser;
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Error - Entered Location");
            notifyUser.exec();
        }

        else {
            std::get<0>(myELocation) = x;
            std::get<1>(myELocation) = y;

            std::cout << "End X = " << std::get<0>(myELocation) << ", end Y = " << std::get<1>(myELocation) << std::endl;

            QMessageBox notifyUser;
            std::string notify = "Location entered successfully. X = " + std::to_string(std::get<0> (myELocation)) + ", Y = " + std::to_string(std::get<1> (myELocation));
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Success - Entered Location");
            notifyUser.exec();
        }
    }
}

void settingsmenu::handleTimerButton() {
    std::string num = txtTimer->text().toStdString();

    if (num.find_first_not_of("1234567890.") != std::string::npos) { // If any other characters are detected, generate an error
        QMessageBox notifyUser;
        notifyUser.setText("Please enter a valid time, in seconds.");
        notifyUser.setWindowTitle("Error - Invalid Timer");
        notifyUser.exec();
    }

    else {
        QMessageBox notifyUser;
        float temp = stof(num);

        if (temp <= 5.0) {
            QMessageBox::StandardButton reply;
            std::string timerWarn = "Are you sure you want a " + num + " timer?";
            reply = QMessageBox::question(this, "Warning - Short Timer", QString::fromStdString(timerWarn), QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                myTimer = temp;
                std::string notify = "Timer had been set to " + std::to_string(myTimer) + " seconds.";
                notifyUser.setText(QString::fromStdString(notify));
                notifyUser.setWindowTitle("Success - Timer Set");
                notifyUser.exec();
            }

            else {
                notifyUser.setText("Canceled.");
                notifyUser.setWindowTitle("Canceled Timer");
                notifyUser.exec();
            }
        }

        else {
            myTimer = temp;
            std::string notify = "Timer had been set to " + std::to_string(myTimer) + " seconds.";
            notifyUser.setText(QString::fromStdString(notify));
            notifyUser.setWindowTitle("Success - Timer Set");
            notifyUser.exec();
        }
    }
}

// getters, called whenever "apply settings" is clicked
std::tuple<float, float> settingsmenu::getSLocation() {
    return mySLocation;
}

std::tuple<float, float> settingsmenu::getELocation() {
    return myELocation;
}

float settingsmenu::getTimer() {
    return myTimer;
}

// setters, called only to load previous settings
void settingsmenu::setSLocation(std::tuple<float, float> startLocation) {
    mySLocation = startLocation;
}

void settingsmenu::setELocation(std::tuple<float, float> endLocation) {
    myELocation = endLocation;
}

void settingsmenu::setTimer(float timer) {
    myTimer = timer;
    std::cout << "timer set: " << myTimer << std::endl;
}
