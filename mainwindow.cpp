#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mapwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::quitApp);
    this->setFixedSize(QSize(350, 430));
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::createNewWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quitApp()
{
    QApplication::quit();
}

void MainWindow::createNewWindow()
{
    MapWindow *testik = new MapWindow(nullptr);
    connect(testik, &MapWindow::windowShown, this, &MainWindow::close);
    testik->disableEditing();
    testik->updateObstacleCounter();
    testik->updateControlledRobotCounter();
    testik->updateEnemyCounter();
    testik->show();
}

