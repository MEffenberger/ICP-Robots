
#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QShowEvent>
#include <QComboBox>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDatabase>
#include <QFont>
#include <QDebug>
#include <QToolBar>

namespace Ui {
class MapWindow;
}

class MapWindow : public QWidget {
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    void updateObstacleCounter();
    void updateControlledRobotCounter();
    void updateEnemyCounter();
    void updateTimer();
    void disableEditing();

    QJsonArray* fillFile(bool* robotFound);
    QJsonArray *mapData;
    ~MapWindow();
signals:
    void startSession();

private:
    /// UI of the Map
    Ui::MapWindow *ui;
    QComboBox *levelComboBox;
    int obstacleCount;
    int controlledRobotsCount;
    int enemyCount;
    bool placingObstacle;
    bool placingRobot;
    bool placingEnemy;
    int timeLimit;
    bool printTime;

private slots:
    void handleCellClicked(int row, int column);
    void toggleObstaclePlacement();
    void toggleRobotPlacement();
    void toggleEnemyPlacement();
    void updateCounts();
    void saveFile();
    void setTimer();
    void startGame();
    void loadMap();
};

#endif // MAPWINDOW_H
