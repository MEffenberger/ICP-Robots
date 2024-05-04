/**
 * @file user.h
 * @brief User class header file
 * @version 1.0
 * @details This class is responsible for creating and moving the User robot
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#ifndef USER_H
#define USER_H

#include <QGraphicsEllipseItem>
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
#include "star.h"


/**
 * @brief User class, inherits from QObject and QGraphicsEllipseItem
 */
class User : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:

    /**
     * @brief User constructor
     * @param parent Parent QGraphicsItem
     * @param orientation Orientation of the user
     * @param velocity Velocity of the user
     */
    User(QGraphicsItem *parent = 0,  int orientation = 0, int velocity = 5);

    /**
     * @brief User destructor
     */
    ~User();

    /**
     * @brief Move the user using keyboard
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    /** A little dot representing the vision point */
    QGraphicsEllipseItem *visionPoint;

private:

    /** Speed of the user */
    qreal speed;

    /** Rotation speed of the user */
    qreal rotationSpeed;

    /** Stunned flag */
    bool Stunned;

    /** Timer for the stun effect */
    QTimer *StunnedTimer;

    /** Timer for the movement */
    QTimer *ForwardTimer;

    /** Timer for the clockwise rotation */
    QTimer *ClockwiseTimer;

    /** Timer for the counter clockwise rotation */
    QTimer *CounterClockwiseTimer;

    /** List of stars */
    QList<Star *> stars;

    /** Number of lives */
    int numberOfLives;

    /** Timer for the cooldown after being hit */
    QTimer *coolDown;

    /** Flag for the cooldown */
    bool isCoolingDown;

    /** Remaining time of the stun */
    int remainingStunnedTime;

    /** Remaining time of the cooldown */
    int remainingCoolDownTime;

    /** Flag for not moving forward if hit the Enemy */
    bool hit;


public slots:

    /**
     * @brief Start the clockwise rotation
     */
    void startRotatingClockwise();

    /**
     * @brief Start the counter clockwise rotation
     */
    void startRotatingCounterClockwise();

    /**
     * @brief Stop the rotation
     */
    void stopRotating();

    /**
     * @brief Stop the movement
     */
    void stopMoving();

    /**
     * @brief Start the movement
     */
    void startMovingForward();

    /**
     * @brief Decrease the number of lives (3 default)
     */
    void decreaseLives();

    /**
     * @brief Set the User as focusable (keyboard control)
     */
    void switchControl();

    /**
     * @brief Stop all timers
     */
    void stopAllTimers();

    /**
     * @brief Resume all timers
     */
    void resumeAllTimers();

private slots:

    /**
     * @brief Stun timer expired
     */
    void StunTimerExpired();

    /**
     * @brief Check for the collisions using the collidingItems() method
     */
    void CheckCollisions();

    /**
     * @brief Function to spawn the Star objects
     */
    void spawnStars();

    /**
     * @brief Function to move the User forward
     */
    void moveForward();

    /**
     * @brief Function to rotate the User clockwise
     */
    void rotateClockwise();

    /**
     * @brief Function to rotate the User counter clockwise
     */
    void rotateCounterClockwise();

    /**
     * @brief Function to end the cooldown
     */
    void endCoolDown();

signals:

    /**
     * @brief Signal emitted when the User is stunned
     */
    void stunned();

    /**
     * @brief Signal emitted when the User is hit mapped to life3
     */
    void deleteLife3();

    /**
     * @brief Signal emitted when the User is hit mapped to life2
     */
    void deleteLife2();

    /**
     * @brief Signal emitted when the User is hit mapped to life1
     */
    void deleteLife1();
};

#endif // USER_H