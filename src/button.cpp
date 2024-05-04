/**
 * @file button.cpp
 * @brief Button class implementation file
 * @version 1.0
 * @details This class is responsible for creating buttons in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "button.h"
#include <utility>


Button::Button(const QPixmap &pixmap, std::string name, QGraphicsItem *parent, qreal x, qreal y) : QGraphicsRectItem(parent) {
    // set the size and he texture of the button
    setRect(0, 0, x, y);
    QPixmap scaledPixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(scaledPixmap);
    setBrush(brush);
    // the button is not supposed to have a border, though it can be set
    setBorderWidth(0);
    this->name = std::move(name);
    // make the button focusable and accept hover events
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setAcceptHoverEvents(true);

    // Set the autopilot rectangle
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
    // border defaults to invisible but can be set
    if (width == 0) {
        pen = QPen(Qt::NoPen);
    } else {
        pen.setWidth(width);
    }
    this->setPen(pen);
}

