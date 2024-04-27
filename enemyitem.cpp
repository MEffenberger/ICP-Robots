#include "enemyitem.h"

EnemyItem::~EnemyItem() {}

int EnemyItem::getOrientation(){
    return orientation;
}

int EnemyItem::getDistance(){
    return distance;
}

int EnemyItem::getRotationAngle(){
    return rotationAngle;
}

int EnemyItem::getVelocity(){
    return velocity;
}

void EnemyItem::setOrientation(int orientation){
    this->orientation = orientation;
}

void EnemyItem::setDistance(int distance){
    this->distance = distance;
}

void EnemyItem::setRotationAngle(int rotationAngle){
    this->rotationAngle = rotationAngle;
}

void EnemyItem::setVelocity(int velocity){
    this->velocity = velocity;
}
