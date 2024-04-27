#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mapwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(350, 430));
    int fontId = QFontDatabase::addApplicationFont(":/Orbitron//static/Orbitron-ExtraBold.ttf");
    if (fontId == -1) {
        exit(1);
    }
    QStringList familyNames = QFontDatabase::applicationFontFamilies(fontId);
    QString fontFamily = familyNames.at(0);
    QString styleSheet = QString("font-family: %1; color: rgb(255, 255, 255); background-image: url(:/images/bar.png);").arg(fontFamily);
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

void MainWindow::loadFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load Map", "", "JSON Files (*.json)");
    if (filename.isEmpty()) return; // Nothing to do

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    QJsonArray mapData = doc.array();
    for (const QJsonValueRef &cellValue : mapData) {
        QJsonObject cellObject = cellValue.toObject();
        QString type = cellObject["type"].toString();
        QJsonObject attributesObject = cellObject["position"].toObject();
        int x = attributesObject["x"].toInt();
        int y = attributesObject["y"].toInt();
        if (type == "Robot") {
            qDebug() << "ROBOT\n";
            QJsonObject attributesObject = cellObject["attributes"].toObject();
            int orientation = attributesObject["orientation"].toInt();
            int rotationAngle = attributesObject["rotationAngle"].toInt();
            int velocity = attributesObject["velocity"].toInt();
            qDebug() << orientation << rotationAngle << velocity;
            qDebug() << "X:" << x << "Y:" << y;
        } else if (type == "Obstacle") {
            qDebug() << "OBSTACLE\n";
            qDebug() << "X:" << x << "Y:" << y;
        } else if (type == "Enemy") {
            qDebug() << "ENEMY\n";
            QJsonObject attributesObject = cellObject["attributes"].toObject();
            int distance = attributesObject["distance"].toInt();
            int orientation = attributesObject["orientation"].toInt();
            int rotationAngle = attributesObject["rotationAngle"].toInt();
            int velocity = attributesObject["velocity"].toInt();
            qDebug() << orientation << distance << rotationAngle << velocity;
            qDebug() << "X:" << x << "Y:" << y;
        } else if(type == "TimeLimit"){
            qDebug() << "TIME\n";
            QJsonObject attributesObject = cellObject["time"].toObject();
            int time = attributesObject["seconds"].toInt();
            qDebug() << time;
        }
    }

}

void MainWindow::createNewWindow()
{
    MapWindow *testik = new MapWindow(nullptr);
    connect(testik, &MapWindow::windowShown, this, &MainWindow::close);
    testik->disableEditing();
    testik->updateObstacleCounter();
    testik->updateControlledRobotCounter();
    testik->updateEnemyCounter();
    testik->updateTimer();
    testik->show();
}

