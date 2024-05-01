
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

typedef struct pixmapIcons {
    QPixmap obstacle;
    QPixmap robot;
    QPixmap enemy;
} pixMapIcons;

class MapWindow : public QWidget {
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    void updateObstacleCounter();
    void updateRobotCounter();
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
    QFont customFont;

    int obstaclesPlaced;
    int robotsPlaced;
    int enemiesPlaced;

    bool placingObstacle;
    bool placingRobot;
    bool placingEnemy;
    int timeLimit;
    bool printTime;
    pixMapIcons icons;

private slots:
    void handleCellClicked(int row, int column);
    void toggleObstaclePlacement();
    void toggleRobotPlacement();
    void toggleEnemyPlacement();
    void clearMap();
    void saveFile();
    void setTimer();
    void startGame();
    void loadMap();
    void loadFont();
};

#endif // MAPWINDOW_H
