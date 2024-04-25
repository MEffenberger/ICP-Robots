//
// Created by marek on 24.04.2024.
//

#include "enemy.h"


Enemy::Enemy(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 100, 100); // Set the size of the ellipse
    QColor lightYellow(0, 0, 0); // RGB color for light yellow
    setBrush(lightYellow);

    setFlag(QGraphicsItem::ItemClipsToShape);

    // The armor is needed so the vision field is not visible where it intersects with the Enemy
    armor = new QGraphicsEllipseItem(0, 0, 100, 100, this); // Set the size of the ellipse
    QPixmap pixmap("../enemy.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    armor->setBrush(pixmap);
    armor->setZValue(1); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(20, 50, 10, 10, this); // Positioned above the center of the User
    visionPoint->setBrush(Qt::red); // Set the color to red
    visionPoint->setZValue(2); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision rectangle
    QVector<QPointF> points;
    points << QPointF(-50, 90)  // Bottom-right point (further right and down)
           << QPointF(20, 70)  // Top-left point
           << QPointF(20, 30)   // Top-right point
           << QPointF(-50, 10); // Bottom-left point (further left and down)

    // Create the vision trapezoid
    visionField = new QGraphicsPolygonItem(QPolygonF(points), this);
    QColor semiTransparentBlue(Qt::yellow); // RGBA color: semi-transparent
    visionField->setPen(QPen(Qt::transparent));
    visionField->setBrush(semiTransparentBlue);
    visionField->setZValue(-1); // Below the Enemy:

    // Initialize movement parameters
    turningAngle = 30;
    clockwise = true;// Initialize movement parameters
    speed = 5.0;
    rotationSpeed = 10.0;
    userCollisionFlag = false;
    QTimer *movementTimer = new QTimer(this);
    QObject::connect(movementTimer, &QTimer::timeout, this, &Enemy::autonomousMovement);
    movementTimer->start(50);
    setTransformOriginPoint(50, 50);
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
    QColor semiTransparentBlue(Qt::yellow); // RGBA color: semi-transparent
    visionField->setBrush(semiTransparentBlue);

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
    if (!(newX >= 0 && newX <= scene()->width() - rect().width() && newY >= 0 &&
        newY <= scene()->height() - rect().height())) {
        // Apply the movement if within the scene
        if (clockwise){
            setRotation(rotation() - turningAngle);
        }
        else {
            setRotation(rotation() + turningAngle);
        }
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
        // set the color of the vision field to blue semi transparent
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
        // set the color of the vision field to blue semi transparent
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

void Enemy::userCollision(User *user){
    // Handle collision with user
    if (visionField->collidesWithItem(user)){
        // change color of visionField to red
        QColor red(255, 0, 0, 100); // RGBA color: semi-transparent red
        visionField->setBrush(red);
        return;
    }
    if (armor->collidesWithItem(user)) {
        // the user is dead, game over
        // debug as of now
        qDebug() << "User is dead";
        return;
    }
}