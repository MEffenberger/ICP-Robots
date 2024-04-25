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


class HorizontalUpperBar : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
    HorizontalUpperBar();

private:
    int width;
    int height;
    int x;
    int y;
    QGraphicsRectItem *Timer;
    QGraphicsRectItem *Pause;
};

class HorizontalLowerBar : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
    HorizontalLowerBar(User *user);

private:
    int width{};
    int height{};
//    QGraphicsRectItem *Name{};
    Button *ForwardButton;
    Button *ClockwiseButton;
    Button *CounterClockwiseButton;
};


#endif //ICP_HORIZONTALBAR_H
