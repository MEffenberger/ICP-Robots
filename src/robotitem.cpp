/**
 * @file robotitem.cpp
 * @brief Robot Item Class Implementation file
 * @version 1.0
 * @details This class is responsible for holding the contorolled robot cell item data in the game
 * @project ICP Project - Epic Robot Survival
 * @author Samuel Hejnicek
 */

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

