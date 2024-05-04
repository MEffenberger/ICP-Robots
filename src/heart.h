/**
 * @file heart.h
 * @brief Heart class header file
 * @version 1.0
 * @details This class is responsible for creating Heart Icons in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

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

/**
 * @brief Heart class, inherits from QObject and QGraphicsRectItem
 */
class Heart : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:

    /**
     * @brief Heart constructor
     * @param parent Parent QGraphicsItem
     */
    explicit Heart(QGraphicsItem *parent = 0);

    /**
     * @brief Heart destructor
     */
    ~Heart() = default;

public slots:

    /**
     * @brief Sets Heart as dead - turns it gray
     */
    void setDead();
};


#endif //ICP_HEART_H
