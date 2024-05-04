#ifndef ROBOTITEM_H
#define ROBOTITEM_H


#include "qtablewidget.h"
/**
 * @brief The RobotItem class
 * 
 * This class is used to store the data of the robot in the QWidgetTable
 */
class RobotItem : public QTableWidgetItem {
private:
    int orientation;
    int velocity;

public:
    RobotItem(int orientation = 0, int velocity = 0){
        this->orientation = orientation;
        this->velocity = velocity;
    }

    ~RobotItem();

    /**
     * @brief Gets the orientation of the robot
     * 
     * @return int orientation
     */
    int getOrientation();

    /**
     * @brief Sets the orientation of the robot
     * 
     * @param orientation orientation of the robot
     */
    void setOrientation(int orientation);

    /**
     * @brief Sets the velocity of the robot
     * 
     * @param velocity velocity of the robot
     */
    void setVelocity(int velocity);

    /**
     * @brief Gets the velocity of the robot
     * 
     * @return int velocity
     */
    int getVelocity();
};


#endif // ROBOTITEM_H
