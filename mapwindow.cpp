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
    icons.obstacle = QPixmap("../images/obstacle.png");
    icons.robot = QPixmap("../images/user3.png");
    icons.enemy = QPixmap("../images/enemy2.png");

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
    QJsonArray* mapData = new QJsonArray();
    QJsonObject timeLimitObject;
    timeLimitObject["type"] = "TimeLimit";
    timeLimitObject["time"] = QJsonObject({
        {"seconds", this->timeLimit}
    });
    mapData->append(timeLimitObject);
    *robotFound = false;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (!item) continue; // Skip empty cells

            QJsonObject cellObject;

            // Get coordinates relative to the QTableWidget
            QPoint cellPosition = ui->tableWidget->visualItemRect(item).topLeft();

            if (RobotItem *robot = dynamic_cast<RobotItem*>(item)) {
                *robotFound = true;
                cellObject["type"] = "Robot";
                cellObject["position"] = QJsonObject({
                    {"x", cellPosition.x()},
                    {"y", cellPosition.y()}
                });
                cellObject["attributes"] = QJsonObject({
                    {"orientation", robot->getOrientation()},
                    {"velocity", robot->getVelocity()}
                });

            } else if (ObstacleItem *obstacle = dynamic_cast<ObstacleItem*>(item)) {
                cellObject["type"] = "Obstacle";
                cellObject["position"] = QJsonObject({
                    {"x", cellPosition.x()},
                    {"y", cellPosition.y()}
                });

            } else if (EnemyItem *enemy = dynamic_cast<EnemyItem*>(item)) {
                cellObject["type"] = "Enemy";
                cellObject["position"] = QJsonObject({
                    {"x", cellPosition.x()},
                    {"y", cellPosition.y()}
                });
                cellObject["attributes"] = QJsonObject({
                    {"orientation", enemy->getOrientation()},
                    {"distance", enemy->getDistance()},
                    {"rotationAngle", enemy->getRotationAngle()},
                    {"velocity", enemy->getVelocity()}
                });
            } else {
                continue;
            }
            mapData->append(cellObject);
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
    clearMap();
    QString filename = QFileDialog::getOpenFileName(this, "Load Map", "", "JSON Files (*.json)");
    if (filename.isEmpty()) return;

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
        int col = attributesObject["x"].toInt() / 75;
        int row = attributesObject["y"].toInt() / 75;

        if (type == "Robot") {
            qDebug() << "ROBOT\n";
            QJsonObject attributesObject = cellObject["attributes"].toObject();

            RobotItem* robotItem = new RobotItem;
            int orientation = attributesObject["orientation"].toInt();
            robotItem->setOrientation(orientation);
            robotItem->setVelocity(attributesObject["velocity"].toInt());
            qDebug() << orientation << attributesObject["velocity"].toInt();

            QPixmap pixmap("../images/user3.png");
            QTransform transform;
            transform.rotate(orientation);
            pixmap = pixmap.transformed(transform);
            robotItem->setFlags(robotItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
            robotItem->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(col),
                                                         ui->tableWidget->rowHeight(row),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation)));
            ui->tableWidget->setItem(row, col, robotItem);
            robotsPlaced++;
            //qDebug() << orientation << rotationAngle << velocity;
            //qDebug() << "X:" << x << "Y:" << y;
        } else if (type == "Obstacle") {
            ObstacleItem* obstacleItem = new ObstacleItem;
            QPixmap pixmap("../images/obstacle.png");
            obstacleItem->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(col),
                                                        ui->tableWidget->rowHeight(row),
                                                        Qt::IgnoreAspectRatio,
                                                        Qt::SmoothTransformation)));
            ui->tableWidget->setItem(row, col, obstacleItem);
            obstaclesPlaced++;
            // qDebug() << "OBSTACLE\n";
            // qDebug() << "X:" << x << "Y:" << y;
        } else if (type == "Enemy") {
            qDebug() << "ENEMY\n";
            QJsonObject attributesObject = cellObject["attributes"].toObject();

            EnemyItem* enemyItem = new EnemyItem;
            int orientation = attributesObject["orientation"].toInt();
            enemyItem->setOrientation(orientation);
            enemyItem->setDistance(attributesObject["orientation"].toInt());
            enemyItem->setRotationAngle(attributesObject["rotationAngle"].toInt());
            enemyItem->setVelocity(attributesObject["velocity"].toInt());

            QPixmap pixmap("../images/enemy2.png");
            QTransform transform;
            transform.rotate(orientation);
            pixmap = pixmap.transformed(transform);
            enemyItem->setFlags(enemyItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
            enemyItem->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(col),
                                                         ui->tableWidget->rowHeight(row),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation)));
            ui->tableWidget->setItem(row, col, enemyItem);
            enemiesPlaced++;
            // qDebug() << orientation << distance << rotationAngle << velocity;
            // qDebug() << "X:" << x << "Y:" << y;
        } else if(type == "TimeLimit"){
            qDebug() << "TIME\n";
            QJsonObject attributesObject = cellObject["time"].toObject();
            this->timeLimit = attributesObject["seconds"].toInt();
            qDebug() << time;
        }
    }
    updateObstacleCounter();
    updateRobotCounter();
    updateEnemyCounter();
    updateTimer();
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
