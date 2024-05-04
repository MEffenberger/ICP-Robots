/**
 * @file obstacle.cpp
 * @brief Obstacle class implementation file
 * @version 1.0
 * @details This class is responsible for creating the obstacles in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "obstacle.h"

Obstacle::Obstacle(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 75, 75); // Set the size of the rectangle
    QPixmap pixmap("images/obstacle4.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    QPen pen = QPen(Qt::NoPen);
    setPen(pen);
}