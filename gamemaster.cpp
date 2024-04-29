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
    connect(mapWindow, &MapWindow::startSession, this, &GameMaster::startGame);

}

void GameMaster::startGame() {
    if(!mainEvent()){
        run();
    }
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
    mainEvent();
}

bool GameMaster::loadFile() {
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
            UserData.push_back(x);
            UserData.push_back(y);
            qDebug() << "ROBOT\n";
            QJsonObject attributesObject = cellObject["attributes"].toObject();
            UserData.push_back(attributesObject["orientation"].toInt());
            UserData.push_back(attributesObject["velocity"].toInt());
            qDebug() << "X:" << x << "Y:" << y;
        } else if (type == "Obstacle") {
            ObstacleData.push_back(std::make_pair(x, y));
            qDebug() << "OBSTACLE\n";
            qDebug() << "X:" << x << "Y:" << y;
        } else if (type == "Enemy") {
            qDebug() << "ENEMY\n";
            EnemyData.push_back(std::vector<int>());
            EnemyData.back().push_back(x);
            EnemyData.back().push_back(y);
            QJsonObject attributesObject = cellObject["attributes"].toObject();
            EnemyData.back().push_back(attributesObject["distance"].toInt());
            EnemyData.back().push_back(attributesObject["orientation"].toInt());
            EnemyData.back().push_back(attributesObject["rotationAngle"].toInt());
            EnemyData.back().push_back(attributesObject["velocity"].toInt());
            qDebug() << "X:" << x << "Y:" << y;
        } else if(type == "TimeLimit"){
            qDebug() << "TIME\n";
            QJsonObject attributesObject = cellObject["time"].toObject();
            timeLimitData = attributesObject["seconds"].toInt();
            qDebug() << timeLimitData;
        }
    }

    if(!userFound){
        QMessageBox::critical(this->mainWindow, "Error", "No user controlled robot found in the map");
        return false;
    }
    return true;
}

bool GameMaster::mainEvent(){
    if(!loadFile()){
        return false;
    }
    this->scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1200, 800);

    QPixmap background("../images/bg.png");
    background = background.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(background);

    this->user = new User(nullptr, UserData[2], UserData[3]);
    scene->addItem(user);
    user->setFlag(QGraphicsItem::ItemIsFocusable); // construktor?
    user->setFocus();
    user->setPos(UserData[0], UserData[1] + 100); // Has to be accounted because of the Horizontal Upper Bar

    this->lowerBar = new HorizontalLowerBar(user);
    scene->addItem(lowerBar);
    lowerBar->setPos(0, 700);
    lowerBar->setZValue(5);

    this->upperBar = new HorizontalUpperBar(user, timeLimitData);
    scene->addItem(upperBar);
    upperBar->setPos(0, 0);
    upperBar->setZValue(5);
    connect(upperBar->pauseButton, &Button::released, this, &GameMaster::pauseTheGame);

    this->popup = new PopUp(nullptr, "gameover");
    scene->addItem(popup);
    popup->setPos(scene->width()/2 - popup->rect().width()/2, scene->height()/2 - popup->rect().height()/2);

    this->popup2 = new PopUp(nullptr, "win");
    scene->addItem(popup2);
    popup2->setPos(scene->width()/2 - popup2->rect().width()/2, scene->height()/2 - popup2->rect().height()/2);

    this->popup3 = new PopUp(nullptr, "paused");
    scene->addItem(popup3);
    popup3->setPos(scene->width()/2 - popup3->rect().width()/2, scene->height()/2 - popup3->rect().height()/2);
    connect(upperBar->pauseButton, &Button::released, popup3, &PopUp::show);
    connect(popup3->resumeButton, &Button::released, popup3, &PopUp::hide);
    connect(popup3->resumeButton, &Button::released, this, &GameMaster::resumeTheGame);
    connect(popup3->restartButton, &Button::released, this, &GameMaster::restartGame);
    connect(popup3->mainMenuButton, &Button::released, this, &GameMaster::headtoMainMenu);
    connect(popup3->exitButton, &Button::released, this, &GameMaster::exitGame);

    for (std::pair<int, int> obstacle : ObstacleData) {
        Obstacle *brick = new Obstacle();
        obstacles.push_back(brick);
        scene->addItem(brick);
        brick->setPos(obstacle.first, obstacle.second + 100);
    }

    for (std::vector<int> enemak : EnemyData) {
        Enemy *enemy = new Enemy(nullptr, user, enemak[2], enemak[3], enemak[5], enemak[4]);
        enemies.push_back(enemy);
        scene->addItem(enemy);
        enemy->setPos(enemak[0], enemak[1] + 100);
        QTimer::singleShot(3000, enemy, &Enemy::startAutonomousMovement);
    }

    this->view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1200, 800);
    user->setFocus();
    view->show();
    return true;
}


void GameMaster::pauseTheGame() {
    this->user->stopAllTimers();
    upperBar->timer->stopTimer();
    for (Enemy *enemy : enemies) {
        if (enemy != nullptr){
        enemy->stopAllTimers();
        }
    }
}

void GameMaster::resumeTheGame() {
    this->user->resumeAllTimers();
    upperBar->timer->continueTimer();
    for (Enemy *enemy : enemies) {
        enemy->resumeAllTimers();
    }
}

void GameMaster::exitGame() {
    QApplication::quit();
}

void GameMaster::headtoMainMenu() {
    this->view->close();
    run();
}

void GameMaster::restartGame() {
    this->view->close();
    startGame();
}