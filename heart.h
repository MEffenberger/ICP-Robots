//
// Created by marek on 26.04.2024.
//

#ifndef ICP_HEART_H
#define ICP_HEART_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


class Heart : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    explicit Heart(QGraphicsItem *parent = 0);
    ~Heart() = default;
public slots:
    void setDead();
};


#endif //ICP_HEART_H
