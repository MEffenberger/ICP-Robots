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
//#include <QSound>
#include "star.h"

class User : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    User(QGraphicsItem *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void aaa();

private:
    QGraphicsEllipseItem *visionPoint;
    qreal speed;
    qreal rotationSpeed;
    bool Stunned;
    QTimer *StunnedTimer;
    QList<Star *> stars;

public slots:
    void moveForward();
    void rotateClockwise();
    void rotateCounterClockwise();

private slots:
    void StunTimerExpired();
    void CheckCollisions();
    void spawnStars(int number);
};

#endif // USER_H