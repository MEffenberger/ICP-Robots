//
// Created by marek on 27.04.2024.
//

#ifndef ICP_GAMEMASTER_H
#define ICP_GAMEMASTER_H

#include <QObject>
#include <map>
#include <vector>
#include <string>
#include "mainwindow.h"
#include "mapwindow.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>




class GameMaster : public QObject {


private:
    std::vector<std::vector<int>> Enemy;
    std::vector<int> User;
    std::pair<int, int> Obstacle;
    int timeLimit;
    //void parseJson();
    MainWindow *mainWindow;
    MapWindow *mapWindow;
    QJsonArray mapData;




public:
    void run();

private slots:
    void startGame();
    void createNewMapWindow();
    void loadFile();
    void showJSONpopup();


};


#endif //ICP_GAMEMASTER_H
