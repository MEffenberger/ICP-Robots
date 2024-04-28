//
// Created by marek on 24.04.2024.
//

#include "enemy.h"


Enemy::Enemy(QGraphicsItem *parent, User *user) : QObject(), QGraphicsEllipseItem(parent)
{
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

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(rect().width()/2, rect().height() - rect().height()/5, 7, 7, this); // Positioned above the center of the User
    visionPoint->setBrush(Qt::red); // Set the color to red
    visionPoint->setZValue(-12); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision rectangle
    visionLength = 5;
    QVector<QPointF> points;
    points << QPointF(rect().width()/2 - rect().width()/5, rect().height() - rect().height()/5)
           << QPointF(0, rect().height() + visionLength*10)
           << QPointF(rect().width(), rect().height() + visionLength*10)
           << QPointF(rect().width()/2 + rect().width()/5, rect().height() - rect().height()/5);

    // Create the vision trapezoid
    visionField = new QGraphicsPolygonItem(QPolygonF(points), this);
    QColor semiTransparentBlue(Qt::yellow); // RGBA color: semi-transparent
    visionField->setPen(QPen(Qt::transparent));
    visionField->setBrush(semiTransparentBlue);
    visionField->setZValue(-1); // Below the Enemy:

    // Initialize movement parameters
    turningAngle = 30;
    clockwise = true;// Initialize movement parameters
    speed = 1.0;
    rotationSpeed = 3.0;
    userCollisionFlag = false;
    QTimer *movementTimer = new QTimer(this);
    QObject::connect(movementTimer, &QTimer::timeout, this, &Enemy::autonomousMovement);
    movementTimer->start(30);
    setTransformOriginPoint(rect().width()/2, rect().width()/2);

    setRotation(180);
    this->user = user;
    connect(this, &Enemy::hit, user, &User::decreaseLives);

    lastPos = pos();
    stuckTimer = new QTimer(this);
    connect(stuckTimer, &QTimer::timeout, this, &Enemy::checkStuck);
    stuckTimer->start(5000);

//    chaseTimer = new QTimer(this);
//    connect(chaseTimer, &QTimer::timeout, this, &Enemy::stopChasing);
}

void Enemy::startAutonomousMovement() {
    // Create a timer
    QTimer *timer = new QTimer();

    // Connect the timer's timeout() signal to the enemy's autonomousMovement() slot
    QObject::connect(timer, &QTimer::timeout, this, &Enemy::autonomousMovement);

    // Start the timer with a delay of 3 seconds (3000 milliseconds)
    timer->start(3000);
}

void Enemy::autonomousMovement(){

    // set the color of the vision field back to yellow
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
    if (!(newX >= 20 && newX <= 1200 - rect().width() - 10 && newY >= 100 + 20 && newY <= 700 - rect().height() - 10)){
        // Apply the movement if within the scene
        if (clockwise){
            setRotation(rotation() - turningAngle);
        }
        else {
            setRotation(rotation() + turningAngle);
        }
    }
    QPointF newPos = QPointF(newX, newY);
    if (QPointF::dotProduct(newPos - lastPos, newPos - lastPos) > 300) { // If moved more than sqrt(500) units
        lastPos = newPos;
        stuckTimer->start(5000); // Restart stuckTimer
    }
    setPos(newX, newY);

}

void Enemy::checkCollisions(){

    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    collidingItems.append(visionField->collidingItems());

    for (QGraphicsItem *item : collidingItems){
        if (Obstacle *obstacle = dynamic_cast<Obstacle *>(item)){
            obstacleCollision(obstacle);
        }
        else if (User *user = dynamic_cast<User *>(item)){
            userCollision(user);
        }
        else if (Enemy *enemy = dynamic_cast<Enemy *>(item) ){
            if (enemy == this) continue;
            enemyCollision(enemy);
        }
    }
}

void Enemy::obstacleCollision(Obstacle *obstacle){
    // Handle collision with obstacle
    userCollisionFlag = false;
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
        // change color of visionField to red
        QColor red(255, 0, 0, 100); // RGBA color: semi-transparent red
        visionField->setBrush(red);
        // Start chasing the user

        qDebug() << "I see you!";

        //TODO implement the chase
        QPointF direction = user->pos() - this->pos();
        qreal angleToUser = atan2(direction.y(), direction.x()) * 180 / M_PI - 90; // Adjust as necessary
        qreal currentAngle = rotation();

        qreal angleDifference = angleToUser - currentAngle;
        // Normalize the angle difference within [-180, 180]
        while (angleDifference < -180) angleDifference += 360;
        while (angleDifference > 180) angleDifference -= 360;

        setRotation(currentAngle + (angleDifference * 0.1));
//
//        chaseTimer->start(3000); // Chase the user for 3 seconds


        return;

    }
    if (armor->collidesWithItem(user)) {
        // the user is dead, game over
        // debug as of now
        qDebug() << "Hit";
        if (clockwise){
            setRotation(rotation() - turningAngle);
        }
        else {
            setRotation(rotation() + turningAngle);
        }
        emitHit();
        return;
    }
}

void Enemy::emitHit() {
    // Emit the hit signal
    emit hit();
}


void Enemy::checkStuck() {
    qDebug() << "Checking if I'm stuck";
    qDebug() << QPointF::dotProduct(pos() - lastPos, pos() - lastPos);
    if (QPointF::dotProduct(pos() - lastPos, pos() - lastPos) < 300) { // If moved less than 10 units
        getUnstuck();
    }
    lastPos = pos(); // Update lastPosition
}

void Enemy::getUnstuck() {
    qDebug() << "STEPBRO I NEED YOUR HELP!";
    setRotation(rotation() + turningAngle);

    // if the enemy is out the scene, move it back
    qreal newX = x();
    qreal newY = y();
    if (newX < 20) newX = 20;
    if (newX > 1200 - rect().width() - 10) newX = 1200 - rect().width() - 10;
    if (newY < 100 + 20) newY = 100 + 20;
    if (newY > 700 - rect().height() - 10) newY = 700 - rect().height() - 10;
    setPos(newX, newY);
}

//void Enemy::stopChasing() {
//    // Stop chasing the user
//    qDebug() << "I lost you!";
//    chaseTimer->stop();
//
//    // Rotate away from the user
//    setRotation(rotation() + 180);
//}