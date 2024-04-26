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
    setPen(QPen(Qt::NoPen));
    this->name = std::move(name);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit pressed();
    qDebug() << "Button " << QString::fromStdString(name) << " is pressed";
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit released();
    qDebug() << "Button " << QString::fromStdString(name) << " is released";
}
