//
// Created by marek on 24.04.2024.
//

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


class Enemy : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    Enemy(QGraphicsItem *parent = 0, User *user = nullptr, int distance = 3, int orientation = 0, int velocity = 3, int rotationAngle = 30);
    ~Enemy();
private:
    QGraphicsEllipseItem *visionPoint;
    QGraphicsPolygonItem *visionField;
    QGraphicsEllipseItem *armor;
    QTimer *movementTimer;
    QTimer *stuckTimer;
    QTimer *chaseTimer;
    qreal speed;
    qreal rotationSpeed;
    qreal turningAngle;
    int visionLength;
    bool clockwise;
    User *user;
    QPointF lastPos;
    int remainingStuckTime;
    int remainingChaseTime;
    bool collision;

protected:

signals:
    void hit();

public slots:
    void startAutonomousMovement();
    void emitHit();
    void checkStuck();
    void getUnstuck();
    void stopChasing();
    void stopAllTimers();
    void resumeAllTimers();


private slots:
    void autonomousMovement();
    void checkCollisions();
    void userCollision(User *user);
    void obstacleCollision(Obstacle *obstacle);
    void enemyCollision(Enemy *enemy);
    //void StunTimerExpired();
    //void CheckCollisions();
};



#endif //ICP_ENEMY_H
