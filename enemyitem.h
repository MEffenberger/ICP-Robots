#ifndef ENEMYITEM_H
#define ENEMYITEM_H

#include "qtablewidget.h"
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

    int getOrientation();
    int getDistance();
    int getRotationAngle();
    void setOrientation(int orientation);
    void setDistance(int distance);
    void setRotationAngle(int rotationAngle);
    void setVelocity(int velocity);
    int getVelocity();
};


#endif // ENEMYITEM_H
