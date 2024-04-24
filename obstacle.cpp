//
// Created by marek on 24.04.2024.
//

#include "obstacle.h"

Obstacle::Obstacle(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 100, 100); // Set the size of the rectangle
}