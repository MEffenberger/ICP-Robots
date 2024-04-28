//
// Created by marek on 24.04.2024.
//

#include "obstacle.h"

Obstacle::Obstacle(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 75, 75); // Set the size of the rectangle
    QPixmap pixmap("../images/obstacle4.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    QPen pen = QPen(Qt::NoPen);
    setPen(pen);
}