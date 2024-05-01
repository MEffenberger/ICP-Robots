#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mapwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->applyGraphics();
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
    this->setWindowTitle("Main menu");
    this->setFixedSize(QSize(350, 430));
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    if (fontId == -1) {
        QApplication::quit();
    }
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QString styleSheet = QString("font-family: %1; color: rgb(0, 255, 0); background-image: url(../images/bar.png);").arg(fontFamily);
    ui->createMapButton->setStyleSheet(styleSheet);
    ui->loadMapButton->setStyleSheet(styleSheet);
    ui->exitButton->setStyleSheet(styleSheet);
}

