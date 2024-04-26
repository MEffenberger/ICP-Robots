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
#include <QSound>
#include "star.h"

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
    QTimer *ForwardTimer;
    QTimer *ClockwiseTimer;
    QTimer *CounterClockwiseTimer;
    QList<Star *> stars;
    int numberOfLives;
    QTimer *coolDown;
    bool isCoolingDown;

public slots:
    void startRotatingClockwise();
    void startRotatingCounterClockwise();
    void stopRotating();
    void stopMoving();
    void startMovingForward();
    void decreaseLives();
    void die();
    void switchControl();

private slots:
    void StunTimerExpired();
    void CheckCollisions();
    void spawnStars(int number);
    void moveForward();
    void rotateClockwise();
    void rotateCounterClockwise();
    void endCoolDown();

signals:
    void stunned();
    void deleteLife3();
    void deleteLife2();
    void deleteLife1();
};

#endif // USER_H