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
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MapWindow::handleCellClicked);
    ui->tableWidget->verticalHeader()->setVisible(false); // Hides the row numbers
    ui->tableWidget->horizontalHeader()->setVisible(false); // Hides the column letters/numbers
    QString styleSheet = "QTableWidget { background-image: url(:/images/background.png); }";
    ui->tableWidget->setStyleSheet(styleSheet);
    // ui->tableWidget->setRowHeight(0, 50); // example row height
    // ui->tableWidget->setColumnWidth(0, 50); // example column width
    // ui->tableWidget->setIconSize(QSize(50, 50)); // Set the size as needed
    setFixedSize(QSize(1200, 720));
    //setStyleSheet("background-color: #B00B69;"); // Replace #f0f0f0 with the desired background color

    QIcon myIcon(":/images/obstacle.png");
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

    //
    ui->levelComboBox->addItem("Level 1", QVariant::fromValue(QPair<int, int>(10, 3)));
    ui->levelComboBox->addItem("Level 2", QVariant::fromValue(QPair<int, int>(15, 4)));
    ui->levelComboBox->addItem("Level 3", QVariant::fromValue(QPair<int, int>(20, 5)));
    connect(ui->levelComboBox, &QComboBox::currentTextChanged, this, &MapWindow::updateObstacleCount);
    //
    //
    QIcon robotIcon(":/images/robot.png");
    ui->pushButton_robot->setIcon(robotIcon);
    ui->pushButton_robot->setIconSize(QSize(40, 40));
    ui->pushButton_robot->setStyleSheet("QPushButton { border-radius: 20px; }");
    connect(ui->pushButton_robot, &QPushButton::clicked, this, &MapWindow::toggleRobotPlacement);
    //
    QIcon enemyIcon(":/images/enemy.png");
    ui->pushButton_enemy->setIcon(enemyIcon);
    ui->pushButton_enemy->setIconSize(QSize(40, 40));
    ui->pushButton_enemy->setStyleSheet("QPushButton { border-radius: 20px; }");
    connect(ui->pushButton_enemy, &QPushButton::clicked, this, &MapWindow::toggleEnemyPlacement);
    //
}

void MapWindow::updateObstacleCount() {
    ui->tableWidget->clear();
    obstacleCount = 0;
    controlledRobotsCount = 0;
    enemyCount = 0;
    updateObstacleCounter();
    updateControlledRobotCounter();
    updateEnemyCounter();
}


MapWindow::~MapWindow() {
    delete ui;
}

void MapWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    emit windowShown();  // Emit the signal when the window is shown
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
    ui->RobotLabel->setText(QString("Controlled robots left: %1").arg(robotsLeft));
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
        // Check if the cell already has an obstacle (by checking the icon)
        if (!item->background().texture().isNull()) {
            // If the cell has an obstacle, remove it
            item->setBackground(QBrush()); // Unset the background
            obstacleCount--; // Decrement the obstacle count
        } else if (obstacleCount < obstacles && item->background().texture().isNull()) {
            QPixmap pixmap(":/images/obstacle.png");
            item->setBackground(QBrush(pixmap.scaled(ui->tableWidget->columnWidth(column),
                                                        ui->tableWidget->rowHeight(row),
                                                        Qt::IgnoreAspectRatio,
                                                        Qt::SmoothTransformation)));


            obstacleCount++; // Increment the obstacle count
        }

        updateObstacleCounter(); // Update the display to show how many obstacles are left

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
                    CustomDialog dialog(this);
                    if (dialog.exec() == QDialog::Accepted) {
                        int orientation = dialog.getOrientation();
                        int distance = dialog.getDistance();
                        int rotationAngle = dialog.getRotationAngle();

                        robotItem->setOrientation(orientation);
                        robotItem->setDistance(distance);
                        robotItem->setRotationAngle(rotationAngle);

                        QPixmap pixmap(":/images/robot.png");
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

                    enemyItem->setOrientation(orientation);
                    enemyItem->setDistance(distance);
                    enemyItem->setRotationAngle(rotationAngle);

                    QPixmap pixmap(":/images/enemy.png");
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
                ui->tableWidget->setItem(row, column, enemyItem);
            }
                updateEnemyCounter();
        }
    }
}
