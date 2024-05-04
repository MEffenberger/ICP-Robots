#include "mapwindow.h"
#include "robotdialog.h"
#include "robotitem.h"
#include "obstacleitem.h"
#include "enemyitem.h"
#include "./ui_mapwindow.h"

MapWindow::MapWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWindow)
{
    ui->setupUi(this);
    
    //Set window name
    this->setWindowTitle("Robot Map Creator");

    //Load custom font to be used in the application
    loadFont();

    //Add icons to the structure
    icons.obstacle = QPixmap("../images/obstacle4.png");
    icons.robot = QPixmap("../images/user3.png");
    icons.enemy = QPixmap("../images/enemy3.png");

    //connect the signals to the slots
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MapWindow::handleCellClicked);
    connect(ui->levelComboBox, &QComboBox::currentTextChanged, this, &MapWindow::clearMap);
    connect(ui->pushButton, &QPushButton::clicked, this, &MapWindow::togglePlacement);
    connect(ui->pushButton_robot, &QPushButton::clicked, this, &MapWindow::togglePlacement);
    connect(ui->pushButton_enemy, &QPushButton::clicked, this, &MapWindow::togglePlacement);
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &MapWindow::saveFile);
    connect(ui->pushButtonTimer, &QPushButton::clicked, this, &MapWindow::setTimer);
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MapWindow::startGame);
    connect(ui->pushButtonMap, &QPushButton::clicked, this, &MapWindow::loadMap);

    //Set the widget table properties
    setFixedSize(QSize(1200, 720));
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    QString styleSheet = "QTableWidget { background-image: url(../images/bg.png); }";
    ui->tableWidget->setStyleSheet(styleSheet);
    
    // Set the initial values of the variables
    this->obstaclesPlaced = 0;
    this->placingObstacle = false;
    this->placingRobot = false;
    this->placingEnemy = false;
    this->robotsPlaced = 0;
    this->enemiesPlaced = 0;
    this->timeLimit = 60;

    //Add levels to the box
    ui->levelComboBox->addItem("Level 1", QVariant::fromValue(QPair<int, int>(10, 3)));
    ui->levelComboBox->addItem("Level 2", QVariant::fromValue(QPair<int, int>(15, 4)));
    ui->levelComboBox->addItem("Level 3", QVariant::fromValue(QPair<int, int>(20, 5)));

    //Apply obstacle icon
    ui->pushButton->setIcon(this->icons.obstacle);
    ui->pushButton->setIconSize(QSize(40, 40));

    //Apply robot icon
    ui->pushButton_robot->setIcon(this->icons.robot);
    ui->pushButton_robot->setIconSize(QSize(40, 40));
    ui->pushButton_robot->setStyleSheet("QPushButton { border-radius: 20px; }");
    
    //Apply enemy robot icon
    ui->pushButton_enemy->setIcon(this->icons.enemy);
    ui->pushButton_enemy->setIconSize(QSize(40, 40));
    ui->pushButton_enemy->setStyleSheet("QPushButton { border-radius: 20px; }");
    
    //Set up the top and bottom bars to hold the buttons
    this->barTop = new QFrame(this);
    this->setBarTop();

    this->barBottom = new QFrame(this);
    this->setBarBottom();
}

void MapWindow::setBarTop(){
    barTop->setStyleSheet("background-image: url(../images/bar.png);");

    //Set the position and resolution of the bar
    barTop->setGeometry(QRect(0, 0, 1231, 61));

    //Make all the buttons children of the bar
    ui->pushButtonTimer->setParent(barTop);
    ui->MapLabel->setParent(barTop);
    ui->ObstacleLabel->setParent(barTop);
    ui->DurationLabel->setParent(barTop);
    ui->EnemyLabel->setParent(barTop);
    ui->RobotLabel->setParent(barTop);
    ui->levelComboBox->setParent(barTop);
    ui->pushButton_robot->setParent(barTop);
    ui->pushButton_enemy->setParent(barTop);
    ui->pushButton->setParent(barTop);

    //Apply custom stylesheet to the buttons
    ui->pushButtonTimer->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(customFont.family()));
    ui->MapLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(customFont.family()));
    ui->ObstacleLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(customFont.family()));
    ui->DurationLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(customFont.family()));
    ui->EnemyLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(customFont.family()));
    ui->RobotLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(customFont.family()));
    ui->levelComboBox->setStyleSheet(QString("font-family: %1; color: rgb(0, 0, 255); background-color: transparent;").arg(customFont.family()));
}

void MapWindow::setBarBottom(){
    barBottom->setStyleSheet("background-image: url(../images/bar.png);");
    
    //Set the position and resolution of the bar
    barBottom->setGeometry(QRect(0, 660, 1231, 61));
    
    //Make all the buttons children of the bar
    ui->pushButtonSave->setParent(barBottom);
    ui->pushButtonStart->setParent(barBottom);
    ui->pushButtonMap->setParent(barBottom);

    //Set the position and resolution of the buttons + apply custom stylesheet
    ui->pushButtonSave->setGeometry(QRect(1000, 10, 191, 41));
    ui->pushButtonSave->setStyleSheet(QString("font-family: %1; color: rgb(255, 255, 0);").arg(customFont.family()));
    ui->pushButtonStart->setGeometry(QRect(455, 10, 231, 41));
    ui->pushButtonStart->setStyleSheet(QString("font-family: %1; color: rgb(255, 0, 0);").arg(customFont.family()));
    ui->pushButtonMap->setGeometry(QRect(10, 10, 131, 41));
    ui->pushButtonMap->setStyleSheet(QString("font-family: %1; color: rgb(255, 255, 0);").arg(customFont.family()));
}

void MapWindow::clearMap(){
    //Clear the map
    ui->tableWidget->clear();

    //Set used variables to 0
    obstaclesPlaced = 0;
    robotsPlaced = 0;
    enemiesPlaced = 0;

    //Default time limit
    timeLimit = 60;

    //Update counters
    updateObstacleCounter();
    updateRobotCounter();
    updateEnemyCounter();
    updateTimer();
}


MapWindow::~MapWindow() {
    delete ui;
}

QJsonArray* MapWindow::fillFile(bool* robotFound){

    //Create a JSON array to store the map data
    QJsonArray* mapData = new QJsonArray();

    //Append time limit
    QJsonObject timeLimitObject;
    timeLimitObject["timeLimit"] = this->timeLimit;
    mapData->append(timeLimitObject);
    
    //Robot must be found in the map
    *robotFound = false;

    //Iterate over whole grid and fill the map data
    for (int rows = 0; rows < ui->tableWidget->rowCount(); rows++) {
        for (int cols = 0; cols < ui->tableWidget->columnCount(); cols++) {
            QTableWidgetItem *item = ui->tableWidget->item(rows, cols);
            QJsonObject mapObject;

            // Get coordinates according to the QTableWidget
            QPoint cellPosition = ui->tableWidget->visualItemRect(item).topLeft();

            //Set robot data
            if (RobotItem *robot = dynamic_cast<RobotItem*>(item)) {
                *robotFound = true;
                mapObject["cellType"] = "Robot";
                mapObject["mapPosition"] = QJsonObject({
                    {"x pos", cellPosition.x()},
                    {"y pos", cellPosition.y()}
                });
                mapObject["parameters"] = QJsonObject({
                    {"orientation", robot->getOrientation()},
                    {"velocity", robot->getVelocity()}
                });

            //Set obstacle data
            } else if (ObstacleItem *obstacle = dynamic_cast<ObstacleItem*>(item)) {
                mapObject["cellType"] = "Obstacle";
                mapObject["mapPosition"] = QJsonObject({
                    {"x pos", cellPosition.x()},
                    {"y pos", cellPosition.y()}
                });

            //Set enemy data
            } else if (EnemyItem *enemy = dynamic_cast<EnemyItem*>(item)) {
                mapObject["cellType"] = "Enemy";
                mapObject["mapPosition"] = QJsonObject({
                    {"x pos", cellPosition.x()},
                    {"y pos", cellPosition.y()}
                });
                mapObject["parameters"] = QJsonObject({
                    {"orientation", enemy->getOrientation()},
                    {"distance", enemy->getDistance()},
                    {"rotationAngle", enemy->getRotationAngle()},
                    {"velocity", enemy->getVelocity()}
                });
            } else {
                continue;
            }
            //Append the cell object to the map data
            mapData->append(mapObject);
        }
    }
    return mapData;
}

void MapWindow::startGame(){
    
    bool robotFound;

    //Save the map internally that user created and emit signal to start the game
    this->mapData = fillFile(&robotFound);
    emit startSession();
}

void MapWindow::loadFont(){

    //Load custom font to be used in the application
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    if (fontId == -1) {
        exit(EXIT_FAILURE);
    }
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily);
    this->customFont = font;
}

void MapWindow::loadMap(){
    //Clear current map
    clearMap();

    //Open file dialog to load the file
    QString filename = QFileDialog::getOpenFileName(this, "Load editor map", "", "JSON Files (*.json)");
    if (filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    //Read the file and parse the data
    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonArray mapData = doc.array();
    
    //Variables to store the position of the cell
    int row, col;

    //Iterate over the loaded data and cell items based on it
    for (const QJsonValueRef &cellValue : mapData) {
        //Get the object from the array
        QJsonObject mapObject = cellValue.toObject();

        //Set time from first field
        if(mapObject.contains("timeLimit")){
            this->timeLimit = mapObject["timeLimit"].toInt();
            updateTimer();
            continue;
        }

        QString type = mapObject["cellType"].toString();
        
        if(mapObject.contains("mapPosition")){
            QJsonObject paramObject = mapObject["mapPosition"].toObject();
            col = paramObject["x pos"].toInt() / SQUARE_SIZE;
            row = paramObject["y pos"].toInt() / SQUARE_SIZE;
        }

        if (type == "Robot") {
            //Load robot data and set cell in the map
            QJsonObject paramObject = mapObject["parameters"].toObject();

            RobotItem* robotItem = new RobotItem;
            int orientation = paramObject["orientation"].toInt();
            robotItem->setOrientation(orientation);
            robotItem->setVelocity(paramObject["velocity"].toInt());
            setTableCell(robotItem, row, col, orientation);
        } else if (type == "Obstacle") {

            //Load obstacle data and set cell in the map
            ObstacleItem* obstacleItem = new ObstacleItem;
            setTableCell(obstacleItem, row, col, 0);
        } else if (type == "Enemy") {
            //Load enemy data and set cell in the map
            QJsonObject paramObject = mapObject["parameters"].toObject();

            EnemyItem* enemyItem = new EnemyItem;
            int orientation = paramObject["orientation"].toInt();
            enemyItem->setOrientation(orientation);
            enemyItem->setDistance(paramObject["orientation"].toInt());
            enemyItem->setRotationAngle(paramObject["rotationAngle"].toInt());
            enemyItem->setVelocity(paramObject["velocity"].toInt());
            setTableCell(enemyItem, row, col, orientation);
        } else {
            continue;
        }
    }

    //Update counters based on loaded data
    updateObstacleCounter();
    updateRobotCounter();
    updateEnemyCounter();
}

void MapWindow::saveFile() {

    //Open file dialog to save the file
    QString filename = QFileDialog::getSaveFileName(this, "Save Map", "", "All Files (*.*)"); 
    if (filename.isEmpty()) {
        return;
    }

    //Add .json ending
    if (!filename.endsWith(".json", Qt::CaseInsensitive)) {
        filename += ".json"; 
    }

    QFile file(filename);

    //If file cannot be opened, return
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    bool playerRobotFound;

    //Fill the file with the map data prepared to be saved
    QJsonArray* mapData = fillFile(&playerRobotFound);

    //If there is no robot in the map, error will pop up
    if(playerRobotFound){
    
    //Save the file
    QJsonDocument saveDoc(*mapData);
    file.write(saveDoc.toJson());
    file.close();
    } else {
        QMessageBox::critical(this, "Error", "Map must contain at least one playable robot.");
    }

}

void MapWindow::setTimer(){
    bool pass;

    //Pops up dialog to set the time limit in given range
    int time = QInputDialog::getInt(this, "Set time limit for level", "Enter time limit (seconds):", 60, 1, 180, 1, &pass);

    //If the input is valid, set the time limit, return otherwise
    if (pass && time > 0) {
        this->timeLimit = time;
    } else {
        return;
    }
    updateTimer();
}

void MapWindow::updateTimer(){
    //Update text next to the timer
    ui->DurationLabel->setText(QString("Duration: %1 (s)").arg(this->timeLimit));
}

void MapWindow::updateObstacleCounter() {
    //Obtain data from level
    QVariant currentData = ui->levelComboBox->currentData();

    //Calculate how many obstacles are left
    int obstaclesLeft = currentData.value<QPair<int, int>>().first - obstaclesPlaced; 

    //Update the text next to the obstacle icon
    ui->ObstacleLabel->setText(QString("Obstacles left: %1").arg(obstaclesLeft));
}

void MapWindow::updateRobotCounter() {

    //Calculate how many robots are left and set the text element
    int robotsLeft = 1 - robotsPlaced;
    ui->RobotLabel->setText(QString("Robots left: %1").arg(robotsLeft));
}

void MapWindow::updateEnemyCounter() {
    //Obtain data from level
    QVariant currentData = ui->levelComboBox->currentData();

    //Calculate how many enemies are left
    int enemyLeft = currentData.value<QPair<int, int>>().second - enemiesPlaced; 

    //Update the text next to the enemy icon
    ui->EnemyLabel->setText(QString("Enemies left: %1").arg(enemyLeft));
}

void MapWindow::disableEditing() {
    //Set not editable flag for all items in the table
    for (int rows = 0; rows < ui->tableWidget->rowCount(); rows++) {
        for (int cols = 0; cols < ui->tableWidget->columnCount(); cols++) {
            QTableWidgetItem *item = ui->tableWidget->item(rows, cols);
            if (!item) {
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(rows, cols, item);
            }
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}

void MapWindow::togglePlacement() {

    //Cast the sender to QPushButton to determine which button was clicked
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button == ui->pushButton) {

        //If other placements are active, disable them
        if(placingRobot){
            placingRobot = false;
            ui->pushButton_robot->setStyleSheet("");
        } else if(placingEnemy){
            placingEnemy = false;
            ui->pushButton_enemy->setStyleSheet("");
        }
        placingObstacle = !placingObstacle; //Toggle the placement mode

    } else if (button == ui->pushButton_robot) {

        //If other placements are active, disable them
        if(placingObstacle){
            placingObstacle = false;
            ui->pushButton->setStyleSheet("");
        } else if(placingEnemy){
            placingEnemy = false;
            ui->pushButton_enemy->setStyleSheet("");
        }
        placingRobot = !placingRobot; //Toggle the placement mode

    } else if (button == ui->pushButton_enemy) {

        //If other placements are active, disable them
        if(placingObstacle){
            placingObstacle = false;
            ui->pushButton->setStyleSheet("");
        } else if(placingRobot){
            placingRobot = false;
            ui->pushButton_robot->setStyleSheet("");
        }
        placingEnemy = !placingEnemy; //Toggle the placement mode
    }
    
    if(placingObstacle || placingRobot || placingEnemy){
        //Make the icon smaller and apply a border to the button
        button->setIconSize(QSize(38, 38));
        button->setStyleSheet("QPushButton {border: 2px solid red; }");
    } else {
        //Reset the style when placement is not active
        button->setStyleSheet("");
    }
}

void MapWindow::clearTableCell(QTableWidgetItem *item, int row, int column){
    //Replace cell with clear one
    QTableWidgetItem *defaultItem = new QTableWidgetItem(); 
    defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, column, defaultItem);
}

void MapWindow::setTableCell(QTableWidgetItem *item, int row, int column, int orientationAngle){

    QPixmap pixmap;
    QTransform transform;
    //Based on cell type, set pixmap and increment the counter
    if(dynamic_cast<ObstacleItem*>(item)){
        obstaclesPlaced++;
        pixmap = this->icons.obstacle;
    } else if(dynamic_cast<RobotItem*>(item)){
        robotsPlaced++;
        pixmap = this->icons.robot;
        //Rotate the robot based on the orientation
        pixmap = pixmap.transformed(transform.rotate(orientationAngle));
    } else if(dynamic_cast<EnemyItem*>(item)){
        enemiesPlaced++;
        pixmap = this->icons.enemy;
        //Rotate the enemy robot based on the orientation
        pixmap = pixmap.transformed(transform.rotate(orientationAngle));
    }
    //Set background
    item->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(column),
                                             ui->tableWidget->rowHeight(row))));

    //Apply not editable flag 
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    //Set item to the table
    ui->tableWidget->setItem(row, column, item);
}

void MapWindow::handleCellClicked(int row, int column) {

    //If no placement is active, return
    if (!placingObstacle && !placingRobot && !placingEnemy) return;

    //Obtain cell item from the table
    QTableWidgetItem *item = ui->tableWidget->item(row, column);

    //Obstale placement
    if(placingObstacle){

        //Obtain maximum number of obstacles for the level
        QVariant currentData = ui->levelComboBox->currentData();
        int obstacles = currentData.value<QPair<int, int>>().first;

        //Cast the item to ObstacleItem
        ObstacleItem *obstacleItem = dynamic_cast<ObstacleItem*>(item);

        //If obstacle is present, remove it
        if (obstacleItem) {
            obstaclesPlaced--;
            clearTableCell(item, row, column);
        } else {
            //If other items are present, return, obstacle cant be placed there
            if (dynamic_cast<EnemyItem*>(item) || dynamic_cast<RobotItem*>(item)) {
                return;
            }

            //If level limit is not reached, place the obstacle
            if (obstaclesPlaced < obstacles) {
                ObstacleItem *obstacleItem = new ObstacleItem();
                setTableCell(obstacleItem, row, column, 0);
            }
        }
        //Update the obstacle counter
        updateObstacleCounter();

    //Robot placement
    } else if (placingRobot) {

        //Cast the item to RobotItem
        RobotItem *robotItem = dynamic_cast<RobotItem*>(item);

        //If robot is present, remove it
        if (robotItem) {
            robotsPlaced--;
            clearTableCell(item, row, column);
        } else {
            //If other items are present, return, robot cant be placed there
            if (dynamic_cast<EnemyItem*>(item) || dynamic_cast<ObstacleItem*>(item)) {
                return; 
            }

            //There can be only one robot for the level
            if (robotsPlaced < 1) {
                RobotItem *robotItem = new RobotItem();

                //Open dialog to set the robot parameters
                RobotParamDialog dialog(this, true);
                if (dialog.exec() == QDialog::Accepted) {
                    int orientation = dialog.getOrientation();

                    robotItem->setOrientation(orientation);
                    robotItem->setVelocity(dialog.getVelocity());

                    setTableCell(robotItem, row, column, orientation);

                } else {
                    //Dialog was closed unsuccesfully, return
                    return;
                }
            }
        }
        updateRobotCounter();

    //Enemy placement
    } else if(placingEnemy){
        //Obtain maximum number of enemies for the level
        QVariant currentData = ui->levelComboBox->currentData();
        int enemies = currentData.value<QPair<int, int>>().second;

        //Cast the item to EnemyItem
        EnemyItem *enemyItem = dynamic_cast<EnemyItem*>(item);

        //If enemy is present, remove it
        if (enemyItem) {
            enemiesPlaced--;
            clearTableCell(item, row, column);
        } else {
            //If other items are present, return, enemy cant be placed there
            if (dynamic_cast<RobotItem*>(item) || dynamic_cast<ObstacleItem*>(item)) {
                return; 
            }

            //If level limit is not reached, place the enemy
            if (enemiesPlaced < enemies) {
                EnemyItem *enemyItem = new EnemyItem();

                //Open dialog to set the enemy parameters
                RobotParamDialog dialog(this);
                if (dialog.exec() == QDialog::Accepted) {
                    int orientation = dialog.getOrientation();

                    enemyItem->setOrientation(orientation);
                    enemyItem->setDistance(dialog.getDistance());
                    enemyItem->setRotationAngle(dialog.getRotationAngle());
                    enemyItem->setVelocity(dialog.getVelocity());

                    setTableCell(enemyItem, row, column, orientation);
                } else {
                    //Dialog was closed unsuccesfully, return
                    return;
                }
            }
        }
        updateEnemyCounter();
    }
}
