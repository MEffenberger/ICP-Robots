//
// Created by marek on 25.04.2024.
//

#include "button.h"

#include <utility>

Button::Button(const QPixmap &pixmap, std::string name, QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    setRect(0, 0, 75, 75);
    QPixmap scaledPixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(scaledPixmap);
    setBrush(brush);
    setPen(QPen(Qt::NoPen));
    this->name = std::move(name);

    timer = new QTimer(this);
    timer->setInterval(50);
    connect(timer, &QTimer::timeout, this, &Button::onTimerTimeout);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit pressed();
    qDebug() << "Button " << QString::fromStdString(name) << " is pressed";
    pressedFlag = true;
    timer->start();
    QGraphicsRectItem::mousePressEvent(event);

}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit released();
    qDebug() << "Button " << QString::fromStdString(name) << " is released";
    pressedFlag = false;
    timer->stop();
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void Button::onTimerTimeout() {
    if (!pressedFlag) return;
    if (name == "Clockwise") {
        emit rotateClockwise();
    } else if (name == "CounterClockwise") {
        emit rotateCounterClockwise();
    } else if (name == "Forward") {
        emit moveForward();
    }
}