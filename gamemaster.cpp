//
// Created by marek on 27.04.2024.
//

#include "gamemaster.h"



void GameMaster::run() {
    qDebug() << "Running";
    this->mainWindow = new MainWindow();
    this->mainWindow->show();
    qDebug() << "Window shown";
    connect(mainWindow, &MainWindow::createNewMapWindow, this, &GameMaster::createNewMapWindow);
    connect(mainWindow, &MainWindow::loadFile, this, &GameMaster::showJSONpopup);
}


void GameMaster::createNewMapWindow() {
    this->mapWindow = new MapWindow();
    emit mainWindow->close();
    this->mainWindow = nullptr;
    mapWindow->disableEditing();
    mapWindow->updateObstacleCounter();
    mapWindow->updateRobotCounter();
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

    if(this->UserData.size() > 0){
        UserData.clear();
    }
    if(this->ObstacleData.size() > 0){
        ObstacleData.clear();
    }
    if(this->EnemyData.size() > 0){
        EnemyData.clear();
    }
    for (const QJsonValueRef &cellValue : *mapData) {
        QJsonObject cellObject = cellValue.toObject();
        QString type = cellObject["type"].toString();
        int x, y;
        if(type != "TimeLimit"){
            QJsonObject attributesObject = cellObject["position"].toObject();
            x = attributesObject["x"].toInt();
            y = attributesObject["y"].toInt();
        }
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
    qDebug() << "Here1";
    this->scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1200, 800);
    qDebug() << "Here2";
    QPixmap background("../images/bg.png");
    background = background.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(background);
    qDebug() << "Here3";
    this->user = new User(nullptr, UserData[2], UserData[3]);
    scene->addItem(user);
    user->setFlag(QGraphicsItem::ItemIsFocusable); // construktor?
    user->setFocus();
    user->setPos(UserData[0], UserData[1] + 100); // Has to be accounted because of the Horizontal Upper Bar
    qDebug() << "Here4";
    this->lowerBar = new HorizontalLowerBar(user);
    scene->addItem(lowerBar);
    lowerBar->setPos(0, 700);
    lowerBar->setZValue(5);

    this->upperBar = new HorizontalUpperBar(user, timeLimitData);
    scene->addItem(upperBar);
    upperBar->setPos(0, 0);
    upperBar->setZValue(5);
    connect(upperBar->pauseButton, &Button::pressed, this, &GameMaster::pauseTheGame);
    qDebug() << "Here5";
    this->popup = new PopUp(nullptr, "gameover");
    scene->addItem(popup);
    popup->setPos(scene->width()/2 - popup->rect().width()/2, scene->height()/2 - popup->rect().height()/2);
    connect(user, &User::deleteLife1, popup, &PopUp::show);
    connect(popup, &PopUp::pauseTimers, this, &GameMaster::pauseTheGame);
    connect(popup->restartButton, &Button::pressed, this, &GameMaster::restartGame);
    connect(popup->mainMenuButton, &Button::pressed, this, &GameMaster::headtoMainMenu);
    connect(popup->exitButton, &Button::pressed, this, &GameMaster::exitGame);

    this->popup2 = new PopUp(nullptr, "win");
    scene->addItem(popup2);
    popup2->setPos(scene->width()/2 - popup2->rect().width()/2, scene->height()/2 - popup2->rect().height()/2);
    connect(upperBar->timer, &Timer::timeIsUp, popup2, &PopUp::show);
    connect(popup2, &PopUp::pauseTimers, this, &GameMaster::pauseTheGame);
    connect(popup2->restartButton, &Button::pressed, this, &GameMaster::restartGame);
    connect(popup2->mainMenuButton, &Button::pressed, this, &GameMaster::headtoMainMenu);
    connect(popup2->exitButton, &Button::pressed, this, &GameMaster::exitGame);

    this->popup3 = new PopUp(nullptr, "paused");
    scene->addItem(popup3);
    popup3->setPos(scene->width()/2 - popup3->rect().width()/2, scene->height()/2 - popup3->rect().height()/2);
    connect(upperBar->pauseButton, &Button::pressed, popup3, &PopUp::show);
    connect(popup3->resumeButton, &Button::pressed, popup3, &PopUp::hide);
    connect(popup3->resumeButton, &Button::pressed, this, &GameMaster::resumeTheGame);
    connect(popup3->restartButton, &Button::pressed, this, &GameMaster::restartGame);
    connect(popup3->mainMenuButton, &Button::pressed, this, &GameMaster::headtoMainMenu);
    connect(popup3->exitButton, &Button::pressed, this, &GameMaster::exitGame);
    qDebug() << "Here6";
    for (std::pair<int, int> obstacle : ObstacleData) {
        Obstacle *brick = new Obstacle();
        obstacles.push_back(brick);
        scene->addItem(brick);
        brick->setPos(obstacle.first, obstacle.second + 100);
    }
    qDebug() << "Here7";
    for (std::vector<int> enemak : EnemyData) {
        Enemy *enemy = new Enemy(nullptr, user, enemak[2], enemak[3], enemak[5], enemak[4]);
        enemies.push_back(enemy);
        scene->addItem(enemy);
        enemy->setPos(enemak[0], enemak[1] + 100);
        QTimer::singleShot(3000, enemy, &Enemy::startAutonomousMovement);
    }
    qDebug() << "Here8";
    this->view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1200, 800);
    user->setFocus();
    user->setFlag(QGraphicsItem::ItemIsFocusable);
    qDebug() << "Here9";
    view->show();
    qDebug() << "Here10";
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
    cleanUp();
    QApplication::quit();
}

void GameMaster::headtoMainMenu() {
    this->view->close();
    run();
}

void GameMaster::restartGame() {
    this->view->close();
    mainEvent();
}

void GameMaster::cleanUp() {
    for (auto &enemy : enemies) {
        delete enemy;
        qDebug() << "Deleted enemy";
    }
    enemies.clear();
    qDebug() << "Deleted all enemies";

    for (auto &obstacle : obstacles) {
        qDebug() << "Deleted obstacle";
        delete obstacle;
    }
    obstacles.clear();
    //UserData.clear(); //SEGFAULTING
    qDebug() << "Deleted all obstacles";

    delete popup3; popup3 = nullptr;
    qDebug() << "Deleted popup3";

    delete popup2; popup2 = nullptr;
    qDebug() << "Deleted popup2";

    delete popup; popup = nullptr;
    qDebug() << "Deleted popup";

    delete upperBar; upperBar = nullptr;
    qDebug() << "Deleted upperBar";

    delete lowerBar; lowerBar = nullptr;
    qDebug() << "Deleted lowerBar";

    delete user; user = nullptr;
    qDebug() << "Deleted user";

    qDebug() << "Cleaned up all game elements";

    //TODO? delete sccene and view?
}
