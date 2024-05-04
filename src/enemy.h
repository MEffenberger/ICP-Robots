/**
 * @file enemy.h
 * @brief Enemy class header file
 * @version 1.0
 * @details This class is responsible for creating autonomous robots
 * (in our implementation - the enemies) in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#ifndef ICP_ENEMY_H
#define ICP_ENEMY_H

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include <QDebug>
#include <QGraphicsScene>
#include "obstacle.h"
#include <cmath>
#include <QGraphicsItem>
#include <QtMath>
#include <QTimer>
#include <QPixmap>
#include <QPainterPath>
#include "user.h"
#include <QGraphicsPolygonItem>

/**
 * @brief Enemy class, inherits from QObject and QGraphicsEllipseItem
 */
class Enemy : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:

    /**
     * @brief Enemy constructor
     * @param parent Parent QGraphicsItem
     * @param user User object
     * @param distance Distance from the obstacles to turn
     * @param orientation Orientation of the enemy
     * @param velocity Velocity of the enemy
     * @param rotationAngle Rotation angle of the enemy
     * (default values shall never be needed)
     */
    Enemy(QGraphicsItem *parent = 0, User *user = nullptr, int distance = 3, int orientation = 0, int velocity = 3, int rotationAngle = 30);

    /**
     * @brief Enemy destructor
     */
    ~Enemy();

private:

    /** Invisible dot used for orientation */
    QGraphicsEllipseItem *visionPoint;

    /** The polygon used as visior field - distance parameter sets the length of the vision field */
    QGraphicsPolygonItem *visionField;

    /** Simply needed for correct texture overlay */
    QGraphicsEllipseItem *armor;

    /** Timers for autonomous movement */
    QTimer *movementTimer;

    /** Timer for checking if the enemy is stuck used for autonomous unstucking mechanism */
    QTimer *stuckTimer;

    /** Timer for chasing the user */
    QTimer *chaseTimer;

    /** Speed of the enemy */
    qreal speed;

    /** Speed of the rotation */
    qreal rotationSpeed;

    /** Distance from the obstacles to turn */
    qreal turningAngle;

    /** Angle of the rotation */
    int visionLength;

    /** Which direction the enemy is turning */
    bool clockwise;

    /** The user object pointer */
    User *user;

    /** The last position of the enemy (used for unstucking) */
    QPointF lastPos;

    /** Remaining time of the enemy being stuck */
    int remainingStuckTime;

    /** Remaining time of the enemy chasing the user */
    int remainingChaseTime;

    /** Checking whether the user collided, currently used if the rotation angle is 0 */
    bool collision;

protected:

signals:

    /**
     * @brief Signal emitted when the enemy collides with the user
     */
    void hit();

public slots:

    /**
     * @brief Start the autonomous movement of the enemy
     */
    void startAutonomousMovement();

    /**
     * @brief After 5s check whether the last position equals (in a set range) the current position
     */
    void checkStuck();

    /**
     * @brief Get the enemy unstuck (rotation and moving out of map boundaries)
     */
    void getUnstuck();

    /**
     * @brief Stop chasing the user
     */
    void stopChasing();

    /**
     * @brief Stop all the timers of the enemy, used for pausing the game
     */
    void stopAllTimers();

    /**
     * @brief Resume all the timers of the enemy, used for resuming the game
     */
    void resumeAllTimers();


private slots:

    /**
     * @brief Move the enemy autonomously, move forward in the direction of the vision point and rotate if needed
     */
    void autonomousMovement();

    /**
     * @brief Check if the enemy is colliding with anything
     */
    void checkCollisions();

    /**
     * @brief Mechanism for collision with the user
     * @param user The user object
     */
    void userCollision(User *user);

    /**
     * @brief Mechanism for collision with an obstacle
     * @param obstacle The obstacle object
     */
    void obstacleCollision(Obstacle *obstacle);

    /**
     * @brief Mechanism for collision with another enemy
     * @param enemy The enemy object
     */
    void enemyCollision(Enemy *enemy);
};



#endif //ICP_ENEMY_H
