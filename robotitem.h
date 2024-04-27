#ifndef ROBOTITEM_H
#define ROBOTITEM_H

#include "qtablewidget.h"
class RobotItem : public QTableWidgetItem {
private:
    int orientation;
    int distance;
    int rotationAngle;
    int velocity;

public:
    RobotItem(int orientation = 0, int distance = 0, int rotationAngle = 0, int velocity = 0){
        this->orientation = orientation;
        this->distance = distance;
        this->rotationAngle = rotationAngle;
        this->velocity = velocity;
    }

    ~RobotItem();

    int getOrientation();
    int getDistance();
    int getRotationAngle();
    void setOrientation(int orientation);
    void setDistance(int distance);
    void setRotationAngle(int rotationAngle);
    void setVelocity(int velocity);
    int getVelocity();
};


#endif // ROBOTITEM_H
