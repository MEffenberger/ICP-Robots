#include "robotitem.h"

RobotItem::~RobotItem() {}

int RobotItem::getOrientation(){
    return orientation;
}

int RobotItem::getDistance(){
    return distance;
}

int RobotItem::getRotationAngle(){
    return rotationAngle;
}

int RobotItem::getVelocity(){
    return velocity;
}

void RobotItem::setOrientation(int orientation){
    this->orientation = orientation;
}

void RobotItem::setDistance(int distance){
    this->distance = distance;
}

void RobotItem::setRotationAngle(int rotationAngle){
    this->rotationAngle = rotationAngle;
}

void RobotItem::setVelocity(int velocity){
    this->velocity = velocity;
}

