//
// Created by marek on 25.04.2024.
//

#include "button.h"


#include <utility>

Button::Button(const QPixmap &pixmap, std::string name, QGraphicsItem *parent, qreal x, qreal y) : QGraphicsRectItem(parent) {
    setRect(0, 0, x, y);
    QPixmap scaledPixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(scaledPixmap);
    setBrush(brush);
    setBorderWidth(0);
    this->name = std::move(name);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setAcceptHoverEvents(true);

    if (this->name == "Forward") {
        autoPilotPosition = QRectF(0, -40, rect().width(), rect().height()); // Set the autopilot rectangle relative to this button
    }

}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit pressed();
    qDebug() << "Button " << QString::fromStdString(name) << " is pressed";
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (this->contains(event->pos())) {
        emit released();
        qDebug() << "Button " << QString::fromStdString(name) << " is released";
    }
    if (name == "Forward" && autoPilotPosition.contains(event->pos())) {
        emit autoPilot();
        qDebug() << "Button " << QString::fromStdString(name) << " is released";
    }
    if(name == "Clockwise" || name == "CounterClockwise") {
        emit released();
        qDebug() << "Button " << QString::fromStdString(name) << " is released";
    }
}

void Button::setBorderWidth(int width) {
    QPen pen;
    if (width == 0) {
        pen = QPen(Qt::NoPen);
    } else {
        pen.setWidth(width);
    }
    this->setPen(pen);
}