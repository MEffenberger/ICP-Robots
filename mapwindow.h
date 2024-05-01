
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
#include <QTableWidgetItem>

namespace Ui {
class MapWindow;
}

/**
 * @brief Struct to store the icons for the pixmap
 * 
 */
typedef struct pixmapIcons {
    QPixmap obstacle;
    QPixmap robot;
    QPixmap enemy;
} pixMapIcons;

/**
 * @brief Class for the Map Window
 * 
 */
class MapWindow : public QWidget {
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);

    /**
     * @brief Updates the number of obstacles to be placed
     * 
     */
    void updateObstacleCounter();

    /**
     * @brief Updates the number of robots to be placed
     * 
     */
    void updateRobotCounter();

    /**
     * @brief Updates the number of enemy robots to be placed
     * 
     */
    void updateEnemyCounter();

    /**
     * @brief Updates the time limit for the game
     * 
     */
    void updateTimer();

    /**
     * @brief Disables editing of the map cells
     * 
     */
    void disableEditing();

    /**
     * @brief Sets up top bar of the map editor
     * 
     */
    void setBarTop();

    /**
     * @brief Sets up bottom bar of the map editor
     * 
     */
    void setBarBottom();

    /**
     * @brief Clears the table cell
     * 
     * @param item pointer to the QTableWidgetItem to be cleared
     * @param row number of the row
     * @param column number of the column
     */
    void clearTableCell(QTableWidgetItem *item, int row, int column);

    /**
     * @brief Sets the table cell
     * 
     * @param item pointer to the QTableWidgetItem to be set
     * @param row number of the row
     * @param column number of the column
     * @param orientationAngle angle of orientation in case of robots
     */
    void setTableCell(QTableWidgetItem *item, int row, int column, int orientationAngle);


    /**
     * @brief Fills the JSON array with the map data
     * 
     * @param robotFound pointer to the boolean variable to check if robot is found
     * @return QJsonArray* pointer to the array with map data
     */
    QJsonArray* fillFile(bool* robotFound);

    ///Json array to store the map data
    QJsonArray *mapData;
    ~MapWindow();
signals:

    /**
     * @brief Signal to start the game
     * 
     */
    void startSession();

private:
    /// UI of the Map
    Ui::MapWindow *ui;

    //Level selector
    QComboBox *levelComboBox;

    //Font to be used in the map editor
    QFont customFont;

    //Top bar of the map editor
    QFrame *barTop;

    //Bottom bar of the map editor
    QFrame *barBottom;

    //Variables to store the number of obstacles, robots and enemies placed
    int obstaclesPlaced;
    int robotsPlaced;
    int enemiesPlaced;
    int timeLimit;

    //Boolean variables to check if the user is placing obstacles, robots or enemies
    bool placingObstacle;
    bool placingRobot;
    bool placingEnemy;

    //Struct to store the icons for the pixmap
    pixMapIcons icons;

private slots:

    /**
     * @brief Handles the cell clicked event
     * 
     * @param row number of the row
     * @param column number of the column
     */
    void handleCellClicked(int row, int column);

    /**
     * @brief Toggles the placement of obstacles, robots and enemies
     * 
     */
    void togglePlacement();

    /**
     * @brief Clears the QTableWidget map and set default values
     * 
     */
    void clearMap();

    /**
     * @brief Saves the map data to a JSON file
     * 
     */
    void saveFile();

    /**
     * @brief Sets the time limit for the game
     * 
     */
    void setTimer();

    /**
     * @brief Starts the game
     * 
     */
    void startGame();

    /**
     * @brief Loads the map from a JSON file
     * 
     */
    void loadMap();

    /**
     * @brief Loads the font for the map editor
     * 
     */
    void loadFont();
};

#endif // MAPWINDOW_H
