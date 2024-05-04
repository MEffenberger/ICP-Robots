/**
 * @file obstacleitem.h
 * @brief Obstacle Item Class Header file
 * @version 1.0
 * @details This class is responsible for holding the obstacle cell item data in the game
 * @project ICP Project - Epic Robot Survival
 * @author Samuel Hejnicek
 */

#ifndef OBSTACLEITEM_H
#define OBSTACLEITEM_H

#include "qtablewidget.h"

/**
 * @brief The ObstacleItem class
 * 
 * This class is used to store the obstacle in the QWidgetTable
 */
class ObstacleItem : public QTableWidgetItem {
    public:
        ObstacleItem() : QTableWidgetItem(){}
};

#endif // OBSTACLEITEM_H
