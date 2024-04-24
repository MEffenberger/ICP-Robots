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

class User : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    User(QGraphicsItem *parent = 0);
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsEllipseItem *visionPoint;
    qreal speed;
    qreal rotationSpeed;
    bool Stunned;
    QTimer *StunnedTimer;

private slots:
    void StunTimerExpired();
    void CheckCollisions();
};

#endif // USER_H