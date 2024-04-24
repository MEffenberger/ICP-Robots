//
// Created by marek on 24.04.2024.
//

#include "enemy.h"


Enemy::Enemy(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 100, 100); // Set the size of the ellipse
    QColor lightYellow(0, 0, 0); // RGB color for light yellow
    setBrush(lightYellow);

    setFlag(QGraphicsItem::ItemClipsToShape);

    // The armor is needed so the vision field is not visible where it intersects with the Enemy
    armor = new QGraphicsEllipseItem(0, 0, 100, 100, this); // Set the size of the ellipse
    QPixmap pixmap("../enemy.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    armor->setBrush(pixmap);
    armor->setZValue(1); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(20, 50, 10, 10, this); // Positioned above the center of the User
    visionPoint->setBrush(Qt::red); // Set the color to red
    visionPoint->setZValue(2); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision rectangle
    QVector<QPointF> points;
    points << QPointF(-50, 90)  // Bottom-right point (further right and down)
           << QPointF(20, 70)  // Top-left point
           << QPointF(20, 30)   // Top-right point
           << QPointF(-50, 10); // Bottom-left point (further left and down)

    // Create the vision trapezoid
    visionField = new QGraphicsPolygonItem(QPolygonF(points), this);
    QColor semiTransparentBlue(Qt::yellow); // RGBA color: semi-transparent
    visionField->setPen(QPen(Qt::transparent));
    visionField->setBrush(semiTransparentBlue);
    visionField->setZValue(-1); // Below the Enemy

    // Initialize movement parameters
    turningAngle = 30;
    clockwise = true;// Initialize movement parameters
    speed = 10.0;
    rotationSpeed = 10.0;
    setTransformOriginPoint(50, 50);

}

//void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    // Now, call the base class paint method to paint the ellipse on top
//    QGraphicsEllipseItem::paint(painter, option, widget);
//}