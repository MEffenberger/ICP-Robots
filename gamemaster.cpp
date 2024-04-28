//
// Created by marek on 27.04.2024.
//

#include "gamemaster.h"



void GameMaster::run() {

    this->mainWindow = new MainWindow();
    this->mainWindow->show();
    connect(mainWindow, &MainWindow::createNewMapWindow, this, &GameMaster::createNewMapWindow);
    connect(mainWindow, &MainWindow::loadFile, this, &GameMaster::showJSONpopup);

}


void GameMaster::createNewMapWindow() {
    this->mapWindow = new MapWindow();
    emit mainWindow->close();
    this->mainWindow = nullptr;
    mapWindow->disableEditing();
    mapWindow->updateObstacleCounter();
    mapWindow->updateControlledRobotCounter();
    mapWindow->updateEnemyCounter();
    mapWindow->updateTimer();
    mapWindow->show();
    connect(mapWindow, &MapWindow::startSession, this, &GameMaster::loadFile);

}

void GameMaster::startGame() {

    //this->mapData = new QJsonArray();
    loadFile();

}

void GameMaster::showJSONpopup() {
    qDebug() << "File opened";
    QString filename = QFileDialog::getOpenFileName(this->mainWindow, "Load Map", "", "JSON Files (*.json)");
    if (filename.isEmpty()) return; // Nothing to do

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    //QJsonArray mapData = doc.array();
    this->mapData = new QJsonArray(doc.array());
    loadFile();
}

void GameMaster::loadFile() {
    if(mainWindow == nullptr){
        this->mapData = mapWindow->mapData;
        emit mapWindow->close();
    } else {
        emit mainWindow->close();
    }
    bool userFound = false;
    QJsonArray*  mapData = this->mapData;
    for (const QJsonValueRef &cellValue : *mapData) {
        QJsonObject cellObject = cellValue.toObject();
        QString type = cellObject["type"].toString();
        QJsonObject attributesObject = cellObject["position"].toObject();
        int x = attributesObject["x"].toInt();
        int y = attributesObject["y"].toInt();
        if (type == "Robot") {
            userFound = true;
            qDebug() << "ROBOT\n";
            QJsonObject attributesObject = cellObject["attributes"].toObject();
            int orientation = attributesObject["orientation"].toInt();
            int velocity = attributesObject["velocity"].toInt();
            qDebug() << orientation << velocity;
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

    if(!userFound){
        QMessageBox::critical(this->mainWindow, "Error", "No user controlled robot found in the map");
        run();
    }
}