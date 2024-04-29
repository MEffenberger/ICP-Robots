//
// Created by marek on 25.04.2024.
//

#ifndef ICP_HORIZONTALBAR_H
#define ICP_HORIZONTALBAR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include "button.h"
#include "user.h"
#include <QGraphicsItem>
#include <QObject>
#include <QPen>
#include <QGraphicsTextItem>
#include <QFontDatabase>
#include "heart.h"
#include "gameinfo.h"
#include "timer.h"


class HorizontalUpperBar : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
    HorizontalUpperBar(User *user, int timeLimit);
    ~HorizontalUpperBar();
    Button *pauseButton;
    Timer *timer;

private:
    int width{};
    int height{};
    //QGraphicsRectItem *Timer;
    //QGraphicsRectItem *Pause;
    Heart *Heart1;
    Heart *Heart2;
    Heart *Heart3;
    GameInfo *gameInfo;
    //User *userPtr;

};

class HorizontalLowerBar : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
    HorizontalLowerBar(User *user);
    ~HorizontalLowerBar();
    QGraphicsRectItem *Autopilot;
private:
    int width{};
    int height{};
    Button *ForwardButton;
    Button *ClockwiseButton;
    Button *CounterClockwiseButton;
    Button *KeyboardButton;

    User *userPtr;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};


#endif //ICP_HORIZONTALBAR_H
