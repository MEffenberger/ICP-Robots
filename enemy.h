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
    Enemy(QGraphicsItem *parent = 0);
private:
    QGraphicsEllipseItem *visionPoint;
    QGraphicsRectItem *visionRect;
    QGraphicsPolygonItem *visionField;
    QGraphicsEllipseItem *armor;
    QTimer *movementTimer;
    qreal speed;
    qreal rotationSpeed;
    qreal turningAngle;
    bool clockwise;
    bool userCollisionFlag;

protected:


public slots:
    void startAutonomousMovement();

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
