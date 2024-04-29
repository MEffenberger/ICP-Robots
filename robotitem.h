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
    RobotItem(int orientation = 0, int velocity = 0){
        this->orientation = orientation;
        this->velocity = velocity;
    }

    ~RobotItem();

    int getOrientation();
    void setOrientation(int orientation);
    void setVelocity(int velocity);
    int getVelocity();
};


#endif // ROBOTITEM_H
