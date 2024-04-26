//
// Created by marek on 25.04.2024.
//

#ifndef ICP_BUTTON_H
#define ICP_BUTTON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <QObject>
#include <QPen>
#include <QTimer>
#include <QDebug>



class Button : public QObject, public QGraphicsRectItem {

    Q_OBJECT

public:
    explicit Button(const QPixmap& pixmap, std::string name, QGraphicsItem *parent = 0);

signals:
    void pressed();
    void released();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    std::string name;
    QTimer *timer;
};


#endif //ICP_BUTTON_H
