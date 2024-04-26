
#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QShowEvent>
#include <QComboBox>
#include <QInputDialog>

namespace Ui {
class MapWindow;
}

class MapWindow : public QWidget {
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    void updateObstacleCounter();
    void setObstacle(int row, int column);
    void toggleObstaclePlacement();
    void toggleRobotPlacement();
    void toggleEnemyPlacement();
    void handleCellClicked(int row, int column);
    void updateObstacleCount();
    void updateControlledRobotCounter();
    void updateEnemyCounter();
    void disableEditing();

    ~MapWindow();
signals:
    void windowShown();  // Signal to notify that the window is shown

protected:
    void showEvent(QShowEvent *event) override;  // Override to detect window show

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
};

#endif // MAPWINDOW_H
