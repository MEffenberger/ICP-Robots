/**
 * @file obstacle.h
 * @brief Obstacle class header file
 * @version 1.0
 * @details This class is responsible for creating the obstacles in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */


#ifndef ICP_OBSTACLE_H
#define ICP_OBSTACLE_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainterPath>

/**
 * @brief Obstacle class, inherits from QGraphicsRectItem
 */
class Obstacle : public QGraphicsRectItem
{
public:

    /**
     * @brief Obstacle constructor
     * @param parent Parent QGraphicsItem
     */
    Obstacle(QGraphicsItem *parent = 0);

    /**
     * @brief Obstacle destructor
     */
    ~Obstacle() = default;

};


#endif //ICP_OBSTACLE_H
