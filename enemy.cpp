//
// Created by marek on 24.04.2024.
//

#include "enemy.h"


Enemy::Enemy(QGraphicsItem *parent, User *user) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 75, 75); // Set the size of the ellipse
    setFlag(QGraphicsItem::ItemClipsToShape);

    // The armor is needed so the vision field is not visible where it intersects with the Enemy
    armor = new QGraphicsEllipseItem(0, 0, 75, 75, this); // Set the size of the ellipse
    QPixmap pixmap("../images/enemy2.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    armor->setBrush(pixmap);
    armor->setZValue(1); // Set the z value to 1 so it's drawn on top of the vision field

    QPen pen;
    pen.setWidth(3); // Set the width of the pen to 3 pixels
    pen.setColor(Qt::black); // Set the color of the pen to black
    setPen(pen);

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(37.5, 56.25, 10, 10, this); // Positioned above the center of the User
    visionPoint->setBrush(Qt::red); // Set the color to red
    visionPoint->setZValue(-12); // Set the z value to 1 so it's drawn on top of the vision field

    // Create the vision rectangle
    visionLength = 5;
    QVector<QPointF> points;
    points << QPointF(25, 56.25)
           << QPointF(0, 75 + visionLength*15)
           << QPointF(75, 75 + visionLength*15)
           << QPointF(50, 56.25);

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
    rotationSpeed = 3.0;
    userCollisionFlag = false;
    QTimer *movementTimer = new QTimer(this);
    QObject::connect(movementTimer, &QTimer::timeout, this, &Enemy::autonomousMovement);
    movementTimer->start(30);
    setTransformOriginPoint(37.5, 37.5);

    setRotation(180);
    this->user = user;
    connect(this, &Enemy::hit, user, &User::decreaseLives);
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
    if (!(newX >= 0 && newX <= 1200 - rect().width() && newY >= 100 + 10 && newY <= 700 - rect().height() - 10)){
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
        emitHit();
        return;
    }
}

void Enemy::emitHit() {
    // Emit the hit signal
    emit hit();
}