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

    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    if (fontId == -1) {
        exit(1);
    }
    QStringList familyNames = QFontDatabase::applicationFontFamilies(fontId);
    QString fontFamily = familyNames.at(0);
    QFont customFont(fontFamily);
    

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MapWindow::handleCellClicked);
    ui->tableWidget->verticalHeader()->setVisible(false); // Hides the row numbers
    ui->tableWidget->horizontalHeader()->setVisible(false); // Hides the column letters/numbers
    QString styleSheet = "QTableWidget { background-image: url(../images/bg.png); }";
    ui->tableWidget->setStyleSheet(styleSheet);
    setFixedSize(QSize(1200, 720));
    // QString styleSheetB = "QWidget { background-image: url(:/images/background.jpg); }";
    // this->setStyleSheet(styleSheetB);


    //setStyleSheet("background-color: #000000;"); // Replace #f0f0f0 with the desired background color

    QIcon myIcon("../images/obstacle.png");
    ui->pushButton->setIcon(myIcon);
    ui->pushButton->setIconSize(QSize(40, 40));
    
    //ui->pushButton->setCheckable(true);
    connect(ui->pushButton, &QPushButton::clicked, this, &MapWindow::toggleObstaclePlacement);
    this->obstacleCount = 0;
    this->placingObstacle = false;
    this->placingRobot = false;
    this->placingEnemy = false;
    this->controlledRobotsCount = 0;
    this->enemyCount = 0;
    this->timeLimit = 60;
    this->printTime = true;
    //
    ui->levelComboBox->addItem("Level 1", QVariant::fromValue(QPair<int, int>(10, 3)));
    ui->levelComboBox->addItem("Level 2", QVariant::fromValue(QPair<int, int>(15, 4)));
    ui->levelComboBox->addItem("Level 3", QVariant::fromValue(QPair<int, int>(20, 5)));
    connect(ui->levelComboBox, &QComboBox::currentTextChanged, this, &MapWindow::updateCounts);
    //
    //
    QIcon robotIcon("../images/user3.png");
    ui->pushButton_robot->setIcon(robotIcon);
    ui->pushButton_robot->setIconSize(QSize(40, 40));
    ui->pushButton_robot->setStyleSheet("QPushButton { border-radius: 20px; }");
    connect(ui->pushButton_robot, &QPushButton::clicked, this, &MapWindow::toggleRobotPlacement);
    //
    QIcon enemyIcon("../images/enemy2.png");
    ui->pushButton_enemy->setIcon(enemyIcon);
    ui->pushButton_enemy->setIconSize(QSize(40, 40));
    ui->pushButton_enemy->setStyleSheet("QPushButton { border-radius: 20px; }");
    connect(ui->pushButton_enemy, &QPushButton::clicked, this, &MapWindow::toggleEnemyPlacement);
    //
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &MapWindow::saveFile);
    ui->pushButtonSave->setFont(customFont);
    connect(ui->pushButtonTimer, &QPushButton::clicked, this, &MapWindow::setTimer);
    ui->pushButtonTimer->setFont(customFont);
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MapWindow::startGame);
    ui->pushButtonStart->setFont(customFont);
    connect(ui->pushButtonMap, &QPushButton::clicked, this, &MapWindow::loadMap);
    ui->pushButtonMap->setFont(customFont);

    //

    ui->ObstacleLabel->setFont(customFont);
    ui->DurationLabel->setFont(customFont);
    ui->EnemyLabel->setFont(customFont);
    ui->RobotLabel->setFont(customFont);
    ui->levelComboBox->setFont(customFont);
    ui->MapLabel->setFont(customFont);
    // ui->MapLabel->setText(QString("ROBOT MAP CREATOR"));
    // ui->ObstacleLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(fontFamily));
    // ui->DurationLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(fontFamily));
    // ui->EnemyLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(fontFamily));
    // ui->RobotLabel->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(fontFamily));
    // ui->levelComboBox->setStyleSheet(QString("font-family: %1; color: rgb(0, 255, 0);").arg(fontFamily));

}

void MapWindow::updateCounts(){
    ui->tableWidget->clear();
    obstacleCount = 0;
    controlledRobotsCount = 0;
    enemyCount = 0;
    timeLimit = 60;
    updateObstacleCounter();
    updateControlledRobotCounter();
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
    this->mapData = fillFile(&robotFound);
    emit startSession();
}

void MapWindow::loadMap(){
    updateCounts();
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
            controlledRobotsCount++;
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
            obstacleCount++;
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
            enemyCount++;
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
    updateControlledRobotCounter();
    updateEnemyCounter();
    updateTimer();
}

void MapWindow::saveFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Save Map", "", "All Files (*.*)"); // Changed filter
    if (filename.isEmpty()) {
        return;
    }

    // Enforce .json extension (since there's no default suggestion anymore)
    if (!filename.endsWith(".json", Qt::CaseInsensitive)) {
        filename += ".json"; 
    }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    bool playerRobotFound;
    QJsonArray* mapData = fillFile(&playerRobotFound);
    if(playerRobotFound){
    QJsonDocument saveDoc(*mapData);
    file.write(saveDoc.toJson());
    file.close();
    } else {
        QMessageBox::critical(this, "Error", "Map must contain at least one playable robot.");
    }

}

void MapWindow::setTimer(){
        bool pass;
        int time = QInputDialog::getInt(this, "Set time limit for level",
                                        "Enter time limit (seconds):", 0, 1, 99, 1, &pass);
        if (pass && time > 0) {
            this->timeLimit = time;
        } else {
            return;
        }
        ui->DurationLabel->setText(QString("Duration: %1 (s)").arg(time));
}

void MapWindow::updateTimer(){
    ui->DurationLabel->setText(QString("Duration: %1 (s)").arg(this->timeLimit));
}


void MapWindow::updateObstacleCounter() {
    QVariant currentData = ui->levelComboBox->currentData();
    int obstaclesLeft = currentData.value<QPair<int, int>>().first - obstacleCount; // Calculate how many obstacles are left
    //int obstaclesLeft = ui->levelComboBox->currentData().toInt() - obstacleCount; // Calculate how many obstacles are left
    //qDebug() << "Obstacles left: " << ui->levelComboBox->currentData().toInt();
    ui->ObstacleLabel->setText(QString("Obstacles left: %1").arg(obstaclesLeft));
}

void MapWindow::updateControlledRobotCounter() {
    int robotsLeft = 1 - controlledRobotsCount;
    //qDebug() << "Obstacles left: " << ui->levelComboBox->currentData().toInt();
    ui->RobotLabel->setText(QString("Robots left: %1").arg(robotsLeft));
}

void MapWindow::updateEnemyCounter() {
    QVariant currentData = ui->levelComboBox->currentData();
    int enemyLeft = currentData.value<QPair<int, int>>().second - enemyCount; 
    //qDebug() << "Obstacles left: " << ui->levelComboBox->currentData().toInt();
    ui->EnemyLabel->setText(QString("Enemies left: %1").arg(enemyLeft));
}

void MapWindow::disableEditing() {
    int rowCount = ui->tableWidget->rowCount();
    int columnCount = ui->tableWidget->columnCount();

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(i, j, item);
            }
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}

void MapWindow::toggleObstaclePlacement() {
    if(placingRobot || placingEnemy) return; 
    placingObstacle = !placingObstacle;  // Toggle the placement mode

    if (placingObstacle) {
        // Apply a style to highlight the button when obstacle placement is active
        ui->pushButton->setIconSize(QSize(38, 38));
        ui->pushButton->setStyleSheet("QPushButton { background-color: yellow; border: 2px solid red; }");
    } else {
        // Reset the style when obstacle placement is not active
        ui->pushButton->setStyleSheet("");
    }
}

void MapWindow::toggleRobotPlacement() {
    if(placingObstacle || placingEnemy) return; // Exit if we're not in robot placement mode
    placingRobot = !placingRobot;  // Toggle the placement mode

    if (placingRobot) {
        // Apply a style to highlight the button when robot placement is active
        ui->pushButton_robot->setIconSize(QSize(38, 38));
        ui->pushButton_robot->setStyleSheet("QPushButton { background-color: yellow; border: 2px solid red; }");
    } else {
        // Reset the style when robot placement is not active
        ui->pushButton_robot->setStyleSheet("");
    }
}

void MapWindow::toggleEnemyPlacement() {
    if(placingObstacle || placingRobot) return; // Exit if we're not in robot placement mode
    placingEnemy = !placingEnemy;  // Toggle the placement mode

    if (placingEnemy) {
        // Apply a style to highlight the button when robot placement is active
        ui->pushButton_enemy->setIconSize(QSize(38, 38));
        ui->pushButton_enemy->setStyleSheet("QPushButton { background-color: yellow; border: 2px solid red; }");
    } else {
        // Reset the style when robot placement is not active
        ui->pushButton_enemy->setStyleSheet("");
    }
}


void MapWindow::handleCellClicked(int row, int column) {
    if (!placingObstacle && !placingRobot && !placingEnemy) return; // Exit if we're not in obstacle placement mode

    QTableWidgetItem *item = ui->tableWidget->item(row, column);

    if(placingObstacle){
        QVariant currentData = ui->levelComboBox->currentData();
        int obstacles = currentData.value<QPair<int, int>>().first;

        ObstacleItem *obstacleItem = dynamic_cast<ObstacleItem*>(item);
        if (obstacleItem) {
            obstacleItem->setBackground(QBrush()); // Unset the background
            obstacleCount--; // Decrement the robot count
            QTableWidgetItem *defaultItem = new QTableWidgetItem();
            defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(row, column, defaultItem);

            updateObstacleCounter();
        } else {
            if (dynamic_cast<EnemyItem*>(item) || dynamic_cast<RobotItem*>(item)) {
                return;
            }

            if (obstacleCount < obstacles) {
                ObstacleItem *obstacleItem = new ObstacleItem();
                QPixmap pixmap("../images/obstacle.png");
                obstacleItem->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(column),
                                                            ui->tableWidget->rowHeight(row),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation)));

                obstacleItem->setFlags(obstacleItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
                obstacleCount++; // Increment the obstacle count
                ui->tableWidget->setItem(row, column, obstacleItem);
            }
        updateObstacleCounter(); // Update the display to show how many obstacles are left
        }
    } else if (placingRobot) {
        RobotItem *robotItem = dynamic_cast<RobotItem*>(item);
            if (robotItem) {
                robotItem->setBackground(QBrush()); // Unset the background
                controlledRobotsCount--; // Decrement the robot count
                QTableWidgetItem *defaultItem = new QTableWidgetItem();
                defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget->setItem(row, column, defaultItem);

                updateControlledRobotCounter();
            } else {
                if (dynamic_cast<EnemyItem*>(item) || dynamic_cast<ObstacleItem*>(item)) {
                    return; 
                }

                if (controlledRobotsCount < 1) {
                    RobotItem *robotItem = new RobotItem();
                    CustomDialog dialog(this, true);
                    if (dialog.exec() == QDialog::Accepted) {
                        int orientation = dialog.getOrientation();
                        int velocity = dialog.getVelocity();

                        robotItem->setOrientation(orientation);
                        robotItem->setVelocity(velocity);

                        QPixmap pixmap("../images/user3.png");
                        QTransform transform;
                        transform.rotate(orientation);
                        pixmap = pixmap.transformed(transform);
                        robotItem->setFlags(robotItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
                        robotItem->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(column),
                                                                     ui->tableWidget->rowHeight(row),
                                                                     Qt::IgnoreAspectRatio,
                                                                     Qt::SmoothTransformation)));
                        
                        controlledRobotsCount++; // Increment the robot count
                    }
                    robotItem->setFlags(robotItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
                    ui->tableWidget->setItem(row, column, robotItem);
                }
                updateControlledRobotCounter();
            }
    } else if(placingEnemy){
        QVariant currentData = ui->levelComboBox->currentData();
        int enemies = currentData.value<QPair<int, int>>().second;
        EnemyItem *enemyItem = dynamic_cast<EnemyItem*>(item);

        if (enemyItem) {
                enemyItem->setBackground(QBrush()); // Unset the background
                enemyCount--; // Decrement the robot count
                QTableWidgetItem *defaultItem = new QTableWidgetItem();
                defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget->setItem(row, column, defaultItem);
                updateEnemyCounter();
        } else {
            if (dynamic_cast<RobotItem*>(item) || dynamic_cast<ObstacleItem*>(item)) {
                return; 
            }

            if (enemyCount < enemies) {
                EnemyItem *enemyItem = new EnemyItem();
                CustomDialog dialog(this);
                if (dialog.exec() == QDialog::Accepted) {
                    int orientation = dialog.getOrientation();
                    int distance = dialog.getDistance();
                    int rotationAngle = dialog.getRotationAngle();
                    int velocity = dialog.getVelocity();

                    enemyItem->setOrientation(orientation);
                    enemyItem->setDistance(distance);
                    enemyItem->setRotationAngle(rotationAngle);
                    enemyItem->setVelocity(velocity);

                    QPixmap pixmap("../images/enemy2.png");
                    QTransform transform;
                    transform.rotate(orientation);
                    pixmap = pixmap.transformed(transform);
                    enemyItem->setFlags(enemyItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
                    enemyItem->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(column),
                                                                    ui->tableWidget->rowHeight(row),
                                                                    Qt::IgnoreAspectRatio,
                                                                    Qt::SmoothTransformation)));
                    
                    enemyCount++; // Increment the robot count
                }
                enemyItem->setFlags(enemyItem->flags() & ~Qt::ItemIsEditable); // Set the ItemIsEditable flag to false
                ui->tableWidget->setItem(row, column, enemyItem);
            }
                updateEnemyCounter();
        }
    }
}
