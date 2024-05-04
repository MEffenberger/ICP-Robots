#include "robotitem.h"

RobotItem::~RobotItem() {}

int RobotItem::getOrientation(){
    return orientation;
}

int RobotItem::getVelocity(){
    return velocity;
}

void RobotItem::setOrientation(int orientation){
    this->orientation = orientation;
}

void RobotItem::setVelocity(int velocity){
    this->velocity = velocity;
}

