//
// Created by marek on 26.04.2024.
//

#include "heart.h"

Heart::Heart(QGraphicsItem *parent) : QGraphicsRectItem(parent) {

    setRect(0, 0, 75, 75);
    QPixmap pixmap("../images/green_heart.png");

    if (pixmap.isNull()) {
        qWarning("Failed to load green_heart.png");
    }

    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QBrush brush(pixmap);
    setBrush(brush);

    setPen(QPen(Qt::NoPen));
}

void Heart::setDead() {
    QPixmap pixmap("../images/gray_heart.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
}