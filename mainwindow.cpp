#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mapwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(350, 430));
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    if (fontId == -1) {
        exit(1);
    }
    QStringList familyNames = QFontDatabase::applicationFontFamilies(fontId);
    QString fontFamily = familyNames.at(0);
    QString styleSheet = QString("font-family: %1; color: rgb(255, 255, 255); background-image: url(../images/bar.png);").arg(fontFamily);
    ui->pushButton->setStyleSheet(styleSheet);
    ui->pushButton_2->setStyleSheet(styleSheet);
    ui->pushButton_3->setStyleSheet(styleSheet);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::createNewWindow);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::quitApp);

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

