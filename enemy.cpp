/**
 * @file enemy.cpp
 * @brief Enemy class implementation file
 * @version 1.0
 * @details This class is responsible for creating autonomous robots
 * (in our implementation - the enemies) in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "enemy.h"


Enemy::Enemy(QGraphicsItem *parent, User *user, int distance, int orientation, int velocity, int rotationAngle ) : QObject(), QGraphicsEllipseItem(parent) {
    setRect(0, 0, 50, 50); // Set the size of the ellipse
    setFlag(QGraphicsItem::ItemClipsToShape);

    // The armor is needed so the vision field is not visible where it intersects with the Enemy
    armor = new QGraphicsEllipseItem(0, 0, 50, 50, this); // Set the size of the ellipse
    QPixmap pixmap("../images/enemy2.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    armor->setBrush(pixmap);
    armor->setZValue(1); // Set the z value to 1 so it's drawn on top of the vision field

    QPen pen;
    pen.setWidth(3); // Set the width of the pen to 3 pixels
    pen.setColor(Qt::black); // Set the color of the pen to black
    setPen(pen);

    // Create the vision point, positioned above the center of the Enemy
    visionPoint = new QGraphicsEllipseItem(rect().width() / 2, rect().height() - rect().height() / 5, 7, 7, this);
    visionPoint->setBrush(Qt::red); // Set the color to red
    visionPoint->setZValue(-12); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision rectangle (the vision field) as of the values 1-5 these are the most suitable
    visionLength = distance;
    QVector<QPointF> points;
    points << QPointF(rect().width() / 2 - rect().width() / 5, rect().height() - rect().height() / 5)
           << QPointF(0, rect().height() + visionLength * 13)
           << QPointF(rect().width(), rect().height() + visionLength * 13)
           << QPointF(rect().width() / 2 + rect().width() / 5, rect().height() - rect().height() / 5);

    visionField = new QGraphicsPolygonItem(QPolygonF(points), this);
    QColor semiTransparentYellow(255,250,205,205);
    visionField->setPen(QPen(Qt::transparent));
    visionField->setBrush(semiTransparentYellow);
    visionField->setZValue(-1); // Below the Enemy children objects

    // Initialize movement parameters
    turningAngle = rotationAngle;
    if (rotationAngle < 0){
        clockwise = false;
    } else {
        clockwise = true;
    }
    // As of the tick time, the velocity counted as such was found the most suitable
    speed = 2 + velocity*0.5;
    rotationSpeed = 3.0;

    // Set the origin point of the transformation - the center of the Enemy
    setTransformOriginPoint(rect().width()/2, rect().width()/2);
    // Set the user pointer
    this->user = user;
    connect(this, &Enemy::hit, user, &User::decreaseLives);

    // Initial last position equals the current position
    lastPos = pos();
    // The enemy shall check whether stucked every 3s
    stuckTimer = new QTimer(this);
    connect(stuckTimer, &QTimer::timeout, this, &Enemy::checkStuck);
    stuckTimer->start(3000);
    // Initialize the chase timer
    chaseTimer = new QTimer(this);
    connect(chaseTimer, &QTimer::timeout, this, &Enemy::stopChasing);
    // Initialize the collision flag
    collision = false;
    // Rotate the enemy so it points upwards (plus the user-given value)
    setRotation(orientation + 180);
    // movementTimer set tu nullptr as it is started after the 3s initial wait
    movementTimer = nullptr;
}


void Enemy::startAutonomousMovement() {
    // Create a timer
    this->movementTimer = new QTimer();
    movementTimer->start(30);

    // Connect the timer's timeout() signal to the enemy's autonomousMovement() slot
    QObject::connect(movementTimer, &QTimer::timeout, this, &Enemy::autonomousMovement);
}


void Enemy::autonomousMovement(){
    // Set the color of the vision field back to yellow
    QColor yellow(255,250,205,205); // RGBA color: semi-transparent
    visionField->setBrush(yellow);

    // Move the Enemy
    QPointF centerPos = mapToScene(rect().center()); // Get the center point in scene coordinates
    QPointF visionPos = mapToScene(visionPoint->rect().center()); // Get the vision point in scene coordinates

    // Calculate the direction from the center to the vision point
    qreal dx = visionPos.x() - centerPos.x();
    qreal dy = visionPos.y() - centerPos.y();

    // Normalize the direction
    qreal len = sqrt(dx * dx + dy * dy);
    dx /= len;
    dy /= len;

    qreal newX = x() + speed * dx;
    qreal newY = y() + speed * dy;

    this->checkCollisions();
    // Check if the new position is within boundaries
    if (!(newX >= 30 && newX <= 1200 - rect().width() - 20 && newY >= 100 + 30 && newY <= 700 - rect().height() - 20)){ //|| collision) {
        // Apply the movement if within the scene
        if (clockwise){
            setRotation(rotation() - (0.7 * turningAngle));
        }
        else {
            setRotation(rotation() + (0.7 * turningAngle));
        }
        collision = true;
    }

    // Restart mechanism for the stuckTimer
    QPointF newPos = QPointF(newX, newY);
    if (QPointF::dotProduct(newPos - lastPos, newPos - lastPos) > 800) { // If moved more than sqrt(800) units
        lastPos = newPos;
        stuckTimer->start(3000); // Restart stuckTimer
    }

    // The enemy shall not move if the rotation angle is 0 and is colliding
    if (turningAngle == 0 && collision) {
        return;
    }
    collision = false;

    // Finally set the new position
    setPos(newX, newY);
}


void Enemy::checkCollisions(){

    // Get the colliding items
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    // Add the colliding items of the vision field
    collidingItems.append(visionField->collidingItems());

    // Go through all of the colliding items, try to cast them to the appropriate type and handle the collision if the
    // cast was successful
    for (QGraphicsItem *item : collidingItems){
        if (Obstacle *obstacle = dynamic_cast<Obstacle *>(item)){
            collision = true;
            obstacleCollision(obstacle);
        }
        else if (User *user = dynamic_cast<User *>(item)){
            collision = true;
            userCollision(user);
        }
        else if (Enemy *enemy = dynamic_cast<Enemy *>(item) ){
            if (enemy == this) continue;
            collision = true;
            enemyCollision(enemy);
        }
    }
}


void Enemy::obstacleCollision(Obstacle *obstacle){
    // Handle collision with obstacle
    if (visionField->collidesWithItem(obstacle)){
        QColor semiTransparentBlue(0,0,255,125); // RGBA color: semi-transparent blue
        visionField->setBrush(semiTransparentBlue);
        // Turn around
        if (clockwise){
            setRotation(rotation() - turningAngle);
        }
        else {
            setRotation(rotation() + turningAngle);
        }
    }
}


void Enemy::enemyCollision(Enemy *enemy) {
    // Handle collision with enemy
    if (visionField->collidesWithItem(enemy)){
        QColor semiTransparentBlue(0,0,255,125);
        visionField->setBrush(semiTransparentBlue);

        // Turn around
        if (clockwise){
            setRotation(rotation() - turningAngle);
        }
        else {
            setRotation(rotation() + turningAngle);
        }
    }
}


void Enemy::userCollision(User *user){
    // Handle collision with user
    if (visionField->collidesWithItem(user) && !(armor->collidesWithItem(user))){
        // Change color of visionField to red
        QColor red(255, 0, 0, 100); // RGBA color: semi-transparent red
        visionField->setBrush(red);
        // Start chasing the user

        qDebug() << "I see you!";

        QPointF direction = user->pos() - this->pos();
        qreal angleToUser = atan2(direction.y(), direction.x()) * 180 / M_PI - 90;
        qreal currentAngle = rotation();

        qreal angleDifference = angleToUser - currentAngle;
        // Normalize the angle difference within [-180, 180]
        while (angleDifference < -180) angleDifference += 360;
        while (angleDifference > 180) angleDifference -= 360;
        // Rotate in the user's direction slowly
        setRotation(currentAngle + (angleDifference * 0.1));

        if(!chaseTimer->isActive()) chaseTimer->start(5000); // Chase the user for 3 seconds

        return;
    }

    if (armor->collidesWithItem(user)) {
        // The user is dead, game over
        qDebug() << "Hit";
        if (clockwise){
            setRotation(rotation() - turningAngle);
        }
        else {
            setRotation(rotation() + turningAngle);
        }

        // Emit the hit signal
        emit hit();
        return;
    }
}


void Enemy::checkStuck() {
    qDebug() << "Checking if I'm stuck";
    qDebug() << QPointF::dotProduct(pos() - lastPos, pos() - lastPos);
    if (QPointF::dotProduct(pos() - lastPos, pos() - lastPos) < 800) {
        getUnstuck();
    }
    lastPos = pos(); // Update lastPosition
}


void Enemy::getUnstuck() {
    qDebug() << "STEPBRO I NEED YOUR HELP!";

    // Rotate the enemy
    setRotation(rotation() + turningAngle);
    // If the enemy is out the scene, move it back
    qreal newX = x();
    qreal newY = y();
    if (newX < 20) newX = 20;
    if (newX > 1200 - rect().width() - 10) newX = 1200 - rect().width() - 10;
    if (newY < 100 + 20) newY = 100 + 20;
    if (newY > 700 - rect().height() - 10) newY = 700 - rect().height() - 10;
    setPos(newX, newY);
}


void Enemy::stopChasing() {
    // Stop chasing the user
    qDebug() << "I lost you!";
    chaseTimer->stop();

    // Rotate away from the user
    setRotation(rotation() + 180);
}


void Enemy::stopAllTimers() {
    // Stop all timers
    remainingStuckTime = stuckTimer->remainingTime();
    remainingChaseTime = chaseTimer->remainingTime();
    if (movementTimer) {
        movementTimer->stop();
    }
    stuckTimer->stop();
    chaseTimer->stop();
}


void Enemy::resumeAllTimers() {
    // Resume all timers
    if (movementTimer) {
        movementTimer->start();
    }
    stuckTimer->start(remainingStuckTime);
    chaseTimer->start(remainingChaseTime);
}


Enemy::~Enemy() {
    if (movementTimer != nullptr) {
        delete movementTimer;
        movementTimer = nullptr;
    }
    if (stuckTimer != nullptr) {
        delete stuckTimer;
        stuckTimer = nullptr;
    }
    if (chaseTimer != nullptr) {
        delete chaseTimer;
        chaseTimer = nullptr;
    }
    if (armor != nullptr) {
        delete armor;
        armor = nullptr;
    }
    if (visionPoint != nullptr) {
        delete visionPoint;
        visionPoint = nullptr;
    }
    if (visionField != nullptr) {
        delete visionField;
        visionField = nullptr;
    }
}