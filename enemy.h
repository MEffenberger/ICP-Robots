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
#include <QSound>


class Enemy : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    Enemy(QGraphicsItem *parent = 0, User *user = nullptr);
private:
    QGraphicsEllipseItem *visionPoint;
    QGraphicsRectItem *visionRect;
    QGraphicsPolygonItem *visionField;
    QGraphicsEllipseItem *armor;
    QTimer *movementTimer;
    qreal speed;
    qreal rotationSpeed;
    qreal turningAngle;
    int visionLength;
    bool clockwise;
    bool userCollisionFlag;
    User *user;
    QPointF lastPos;
    QTimer *stuckTimer;
    QTimer *chaseTimer;


protected:

signals:
    void hit();

public slots:
    void startAutonomousMovement();
    void emitHit();
    void checkStuck();
    void getUnstuck();
    void stopChasing();


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
