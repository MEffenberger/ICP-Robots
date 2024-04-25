//
// Created by marek on 25.04.2024.
//

#include "star.h"

Star::Star(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 20, 20); // Small circle

    QPixmap pixmap("../images/star.png"); // Load the star image
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush); // Set the brush to the star image

    setPen(Qt::NoPen); // No border

    // Timer to update position
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Star::move);
    timer->start(50); // Adjust as needed
}

void Star::move() {
    // Calculate new position based on current rotation
    qreal angle = rotation(); // Use current rotation as base angle
    qreal radius = 50; // should be the same as used in initialization

    // Calculate new position
    qreal newX = parentItem()->boundingRect().center().x() + radius * qCos(qDegreesToRadians(angle));
    qreal newY = parentItem()->boundingRect().center().y() + radius * qSin(qDegreesToRadians(angle));

    setPos(newX, newY);


    // Update rotation to continue the movement
    setRotation(angle + 10); // Rotate further by 10 degrees for each update
}