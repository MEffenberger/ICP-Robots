//
// Created by marek on 24.04.2024.
//

#ifndef ICP_OBSTACLE_H
#define ICP_OBSTACLE_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainterPath>


class Obstacle : public QGraphicsRectItem
{
public:
    Obstacle(QGraphicsItem *parent = 0);

};


#endif //ICP_OBSTACLE_H
