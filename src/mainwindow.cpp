/**
 * @file mainwindow.cpp
 * @brief Main Window Class Implementation file
 * @version 1.0
 * @details This class is responsible for creating the main window of the robot game
 * @project ICP Project - Epic Robot Survival
 * @author Samuel Hejnicek
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mapwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Apply font and background to the main window
    this->applyGraphics();

    //Connect signals and slots
    connect(ui->createMapButton, &QPushButton::clicked, this, &MainWindow::createNewWindow);
    connect(ui->loadMapButton, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::quitApp);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quitApp()
{
    QApplication::quit();
}

void MainWindow::loadGame()
{
    emit loadFile();
}

void MainWindow::createNewWindow()
{
    emit createNewMapWindow();
}

void MainWindow::applyGraphics(){
    //Set the title of the main window
    this->setWindowTitle("Main menu");

    //Set the size of the main window
    this->setFixedSize(QSize(350, 430));

    //Load font
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    if (fontId == -1) {
        QApplication::quit();
    }
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    //Design style sheet
    QString styleSheet = QString("font-family: %1; color: rgb(0, 255, 0); background-image: url(../images/bar.png);").arg(fontFamily);
    //Apply style sheet to the main window buttons
    ui->createMapButton->setStyleSheet(styleSheet);
    ui->loadMapButton->setStyleSheet(styleSheet);
    ui->exitButton->setStyleSheet(styleSheet);
}

