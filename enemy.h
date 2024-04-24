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
    qreal speed;
    qreal rotationSpeed;
    qreal turningAngle;
    bool clockwise;

protected:
    // Override the paint method
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private slots:
    //void StunTimerExpired();
    //void CheckCollisions();
};



#endif //ICP_ENEMY_H
