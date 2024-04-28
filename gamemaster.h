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
#include "user.h"
#include "obstacle.h"
#include "enemy.h"
#include "horizontalbar.h"
#include "popup.h"
#include "mapwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>




class GameMaster : public QObject {


private:
    std::vector<std::vector<int>> EnemyData;
    std::vector<int> UserData;
    std::vector<std::pair<int, int>> ObstacleData;
    int timeLimitData;
    //void parseJson();
    MainWindow *mainWindow;
    MapWindow *mapWindow;
    QJsonArray *mapData;


    std::vector<Enemy*> enemies;
    User *user;
    std::vector<Obstacle*> obstacles;
    HorizontalUpperBar *upperBar;
    HorizontalLowerBar *lowerBar;
    QGraphicsScene *scene;
    PopUp *popup;
    PopUp *popup2;
    PopUp *popup3;
    QGraphicsView *view;



public:
    void run();

private slots:
    void startGame();
    void createNewMapWindow();
    bool loadFile();
    void showJSONpopup();
    bool mainEvent();
    void pauseTheGame();
    void resumeTheGame();


};


#endif //ICP_GAMEMASTER_H
