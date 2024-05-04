/**
 * @file star.cpp
 * @brief Star class implementation file
 * @version 1.0
 * @details This class is responsible for creating and moving little stars when the user is stunned
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "star.h"

Star::Star(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 20, 20);
    QPixmap pixmap("images/star.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    setPen(Qt::NoPen); // No border

    // Timer to update position
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Star::move);
    timer->start(50);
}

void Star::move() {
    // Calculate new position based on current rotation
    qreal angle = rotation();
    qreal radius = 20;
    // Calculate new position, based on the center of the parent item (User)
    qreal newX = parentItem()->boundingRect().center().x() + radius * qCos(qDegreesToRadians(angle));
    qreal newY = parentItem()->boundingRect().center().y() + radius * qSin(qDegreesToRadians(angle));
    setPos(newX, newY);
    // Spin the star
    setRotation(angle + 10);
}