/**
 * @file gamemaster.cpp
 * @brief GameMaster class implementation file
 * @version 1.0
 * @details This class is responsible for correct switching between the game windows
 *          pausing the game, setting up the main menu and the game itself based on the parsed JSON file
 * @source The scene creation and setting up the main game was inspired by
 *         https://www.youtube.com/watch?v=8ntEQpg7gck&list=PLyb40eoxkelOa5xCB9fvGrkoBf8JzEwtV&ab_channel=Abdullah
 * @project ICP Project - Epic Robot Survival
 * @authors Marek Effenberger, Samuel Hejníček
 */

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
    //Load the file
    QString filename = QFileDialog::getOpenFileName(this->mainWindow, "Load game map", "", "JSON Files (*.json)");
    //Filename is empty, return
    if (filename.isEmpty()){
        return;
    }

    //Open file wiwht given filename
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    //Create new QJsonArray from the document and assign it to mapData
    this->mapData = new QJsonArray(doc.array());
    mainEvent();
}

bool GameMaster::loadFile() {
    //MainWindow is closed, mapWindow is open, close the mapwWindow
    if(mainWindow == nullptr){
        this->mapData = mapWindow->mapData;
        emit mapWindow->close();
    } else {
        //Main window is open, close the mainWindow
        emit mainWindow->close();
    }

    //Playable robot must be found
    bool userFound = false;

    QJsonArray*  mapData = this->mapData;

    //If there are any elements stored in vectors, clear them
    if(this->UserData.size() > 0){
        UserData.clear();
    }
    if(this->ObstacleData.size() > 0){
        ObstacleData.clear();
    }
    if(this->EnemyData.size() > 0){
        EnemyData.clear();
    }

    //Iterate through the mapData array
    for (const QJsonValueRef &mapValue : *mapData) {

        //Obtain the object from the array
        QJsonObject mapObject = mapValue.toObject();

        //Obtain time limit data
        if(mapObject.contains("timeLimit")){
            timeLimitData = mapObject["timeLimit"].toInt();
        }

        QString type = mapObject["cellType"].toString();
        //Variables for x and y position
        int x, y;

        //Obtain x and y position if exist
        if(mapObject.contains("mapPosition xcord") && mapObject.contains("mapPosition ycord")){
            x = mapObject["mapPosition xcord"].toInt();
            y = mapObject["mapPosition ycord"].toInt();
        }
        //Store robot data
        if (type == "Robot") {
            userFound = true;
            UserData.push_back(x);
            UserData.push_back(y);
            QJsonObject paramObject = mapObject["parameters"].toObject();
            UserData.push_back(paramObject["orientation"].toInt());
            UserData.push_back(paramObject["velocity"].toInt());
        //Store obstacle data
        } else if (type == "Obstacle") {
            ObstacleData.push_back(std::make_pair(x, y));
        //Store enemy data
        } else if (type == "Enemy") {
            EnemyData.push_back(std::vector<int>());
            EnemyData.back().push_back(x);
            EnemyData.back().push_back(y);
            QJsonObject paramObject = mapObject["parameters"].toObject();
            EnemyData.back().push_back(paramObject["distance"].toInt());
            EnemyData.back().push_back(paramObject["orientation"].toInt());
            EnemyData.back().push_back(paramObject["rotationAngle"].toInt());
            EnemyData.back().push_back(paramObject["velocity"].toInt());
        } else {
            continue;
        }
    }

    //If playable robot was not found, show error message and return false
    if(!userFound){
        QMessageBox::critical(this->mainWindow, "Error", "No user controlled robot found in the map");
        return false;
    }
    return true;
}

bool GameMaster::mainEvent(){

    // If the file was not loaded, return false
    if(!loadFile()){
        return false;
    }

    // Create a fixed size scene
    this->scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1200, 800);
    // Set the background image
    QPixmap background("images/bg.png");
    background = background.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(background);

    // Create the user object
    this->user = new User(nullptr, UserData[2], UserData[3]);
    scene->addItem(user);
    user->setFlag(QGraphicsItem::ItemIsFocusable);
    user->setFocus();
    user->setPos(UserData[0], UserData[1] + 100); // Has to be accounted because of the Horizontal Upper Bar

    // Create the upper and lower bars and set their positions, connect the pause button to the pause function
    this->lowerBar = new HorizontalLowerBar(user);
    scene->addItem(lowerBar);
    lowerBar->setPos(0, 700);
    lowerBar->setZValue(5);

    this->upperBar = new HorizontalUpperBar(user, timeLimitData);
    scene->addItem(upperBar);
    upperBar->setPos(0, 0);
    upperBar->setZValue(5);
    connect(upperBar->pauseButton, &Button::pressed, this, &GameMaster::pauseTheGame);

    // Create the popups for game over, win and pause
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

    // Create the obstacles, set their positions and add them to the scene
    for (std::pair<int, int> obstacle : ObstacleData) {
        Obstacle *brick = new Obstacle();
        obstacles.push_back(brick);
        scene->addItem(brick);
        brick->setPos(obstacle.first, obstacle.second + 100);
    }

    // Create the enemies, set their positions and add them to the scene
    for (std::vector<int> enemak : EnemyData) {
        Enemy *enemy = new Enemy(nullptr, user, enemak[2], enemak[3], enemak[5], enemak[4]);
        enemies.push_back(enemy);
        scene->addItem(enemy);
        enemy->setPos(enemak[0], enemak[1] + 100);
        QTimer::singleShot(3000, enemy, &Enemy::startAutonomousMovement);
    }


    // Create the countDown for the first 3 seconds of the game, use the Orbitron font
    this->countDown = new QGraphicsTextItem();
    int fontId = QFontDatabase::addApplicationFont("Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font;
    font.setFamily(family);
    font.setPointSize(100);
    this->countDown->setFont(font);
    this->countDown->setPos(this->scene->width()/2, this->scene->height()/2);
    QColor color(0,255,0);
    this->countDown->setDefaultTextColor(color);
    this->countDown->setZValue(10);
    this->countDown->setVisible(true);
    scene->addItem(countDown);

    // Every 0.6 seconds, update the countDown
    countDownTimer = new QTimer(this);
    connect(countDownTimer, &QTimer::timeout, this, &GameMaster::updateCountDown);
    countDownTimer->start(600);

    // Set the scene to the view and show the view
    this->view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1200, 800);
    user->setFocus();
    user->setFlag(QGraphicsItem::ItemIsFocusable);
    view->show();
    return true;
}


void GameMaster::pauseTheGame() {
    // Pause all timers
    this->countDownTimer->stop();
    this->user->stopAllTimers();
    upperBar->timer->stopTimer();
    for (Enemy *enemy : enemies) {
        if (enemy != nullptr){
        enemy->stopAllTimers();
        }
    }
}

void GameMaster::resumeTheGame() {
    // Resume all timers
    this->countDownTimer->start(600);
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

    delete countDownTimer; countDownTimer = nullptr;

    delete countDown; countDown = nullptr;

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
    //UserData.clear();
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

void GameMaster::updateCountDown() {
    // Count down from 3 to 0, then start is shown in the middle of the screen, user can move freely but enemies cannot
    static int count = 3;
    if (count > 0) {
        qDebug() << count;
        this->countDown->setPlainText(QString::number(count));
        count--;
    } else if (count == 0) {
        // Set color to red and start
        qDebug() << "START!";
        this->countDown->setDefaultTextColor(QColor(255, 0, 0));
        this->countDown->setPlainText("START!");
        this->user->switchControl();
        count--;
    } else {
        this->countDown->setVisible(false);
    }
    this->countDown->setPos(scene->width()/2 - this->countDown->boundingRect().width()/2,
                            scene->height()/2 - this->countDown->boundingRect().height()/2);
}