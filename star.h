//
// Created by marek on 25.04.2024.
//

#ifndef ICP_STAR_H
#define ICP_STAR_H

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <QtMath>


class Star : public QObject, public QGraphicsEllipseItem {
Q_OBJECT
public:
    Star(QGraphicsItem *parent = 0);
    ~Star() = default;
public slots:
    void move();

};


#endif //ICP_STAR_H
