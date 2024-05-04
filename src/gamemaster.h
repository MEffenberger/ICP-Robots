/**
 * @file gamemaster.h
 * @brief GameMaster class header file
 * @version 1.0
 * @details This class is responsible for correct switching between the game windows
 *          pausing the game, setting up the main menu and the game itself based on the parsed JSON file
 * @project ICP Project - Epic Robot Survival
 * @authors Marek Effenberger, Samuel Hejníček
 */

#ifndef ICP_GAMEMASTER_H
#define ICP_GAMEMASTER_H

#include <QObject>
#include <map>
#include <vector>
#include <string>
#include "mainwindow.h"
#include "mapwindow.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "user.h"
#include "obstacle.h"
#include "enemy.h"
#include "horizontalbar.h"
#include "popup.h"
#include "mapwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>


/**
 * @brief GameMaster class, inherits from QObject
 */
class GameMaster : public QObject {

private:

    /** Vector of EnemyData vectors, representing the parsed data from JSON */
    std::vector<std::vector<int>> EnemyData;

    /** Vector of UserData representing the parsed data from JSON */
    std::vector<int> UserData;

    /** Vector of ObstacleData pairs representing the parsed data from JSON */
    std::vector<std::pair<int, int>> ObstacleData;

    /** Time limit for the game */
    int timeLimitData;

    /** Main Window - the first one which appears when the game is started */
    MainWindow *mainWindow;

    /** Map Window - the window where the user can create the JSON file */
    MapWindow *mapWindow;

    /** JSON file data */
    QJsonArray *mapData;


    /** Vector of enemies */
    std::vector<Enemy*> enemies;

    /** User object */
    User *user;

    /** Vector of obstacles */
    std::vector<Obstacle*> obstacles;

    /** Horizontal upper bar */
    HorizontalUpperBar *upperBar;

    /** Horizontal lower bar */
    HorizontalLowerBar *lowerBar;

    /** Scene for the game */
    QGraphicsScene *scene;

    /** PopUp window for the game over */
    PopUp *popup;

    /** PopUp window for the game victory */
    PopUp *popup2;

    /** PopUp window for the game paused */
    PopUp *popup3;

    /** View for the game */
    QGraphicsView *view;

    /** CountDown for the first 3 seconds of the game */
    QGraphicsTextItem* countDown;

    /** Timer for the countDown */
    QTimer* countDownTimer;

public:

    /**
     * @brief Run the game - initialize the main window
     */
    void run();

private slots:

    /**
     * @brief Start the game - Open the main window
     */
    void startGame();

    /**
     * @brief Create a new map window
     */
    void createNewMapWindow();

    /**
     * @brief Load the JSON file
     */
    bool loadFile();

    /**
     * @brief Show the JSON popup
     */
    void showJSONpopup();

    /**
     * @brief Create the game based on the parsed JSON file
     */
    bool mainEvent();

    /**
     * @brief Pause the game
     */
    void pauseTheGame();

    /**
     * @brief Resume the game
     */
    void resumeTheGame();

    /**
     * @brief Exit the game
     */
    void exitGame();

    /**
     * @brief Head to the main menu
     */
    void headtoMainMenu();

    /**
     * @brief Restart the game
     */
    void restartGame();

    /**
     * @brief Clean up the game, call all the destructors of constructed objects
     */
    void cleanUp();

    /**
     * @brief Update the CountDownTimer every 0.6s
     */
    void updateCountDown();
};


#endif //ICP_GAMEMASTER_H
