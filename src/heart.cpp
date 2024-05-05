/**
 * @file heart.cpp
 * @brief Hnemy class implementation file
 * @version 1.0
 * @details This class is responsible for creating Heart Icons in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "heart.h"


Heart::Heart(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    setRect(0, 0, 75, 75);
    QPixmap pixmap("images/green_heart.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    setPen(QPen(Qt::NoPen));
}


void Heart::setDead() {
    QPixmap pixmap("images/gray_heart.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
}