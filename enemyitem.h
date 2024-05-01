#ifndef ENEMYITEM_H
#define ENEMYITEM_H

#include "qtablewidget.h"
/**
 * @brief The EnemyItem class
 * 
 * This class is used to store the data of the enemy robot in the QWidgetTable
 */
class EnemyItem : public QTableWidgetItem {
private:
    int orientation;
    int distance;
    int rotationAngle;
    int velocity;

public:
    EnemyItem(int orientation = 0, int distance = 0, int rotationAngle = 0, int velocity = 0){
        this->orientation = orientation;
        this->distance = distance;
        this->rotationAngle = rotationAngle;
        this->velocity = velocity;
    }

    ~EnemyItem();

    /**
     * @brief Gets the orientation of the enemy robot
     * 
     * @return int orientation
     */
    int getOrientation();

    /**
     * @brief Gets the distance of the enemy robot
     * 
     * @return int distance
     */
    int getDistance();

    /**
     * @brief Gets the rotation angle of the enemy robot
     * 
     * @return int angle
     */
    int getRotationAngle();

    /**
     * @brief Gets the velocity of the enemy robot
     * 
     * @return int velocity
     */
    int getVelocity();

    /**
     * @brief Sets the orientation of the enemy robot
     * 
     * @param orientation orientation of the enemy robot
     */
    void setOrientation(int orientation);

    /**
     * @brief Sets the distance of the enemy robot
     * 
     * @param distance distance of the enemy robot
     */
    void setDistance(int distance);

    /**
     * @brief Sets the rotation angle of the enemy robot
     * 
     * @param rotationAngle rotation angle of the enemy robot
     */
    void setRotationAngle(int rotationAngle);

    /**
     * @brief Sets the velocity of the enemy robot
     * 
     * @param velocity velocity of the enemy robot
     */
    void setVelocity(int velocity);
    
};


#endif // ENEMYITEM_H
