/**
 * @file user.cpp
 * @brief User class implementation file
 * @version 1.0
 * @details This class is responsible for creating and moving the User robot
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "user.h"
// Needed for the collision detection, class Enemy is used in the CheckCollisions method
#include "enemy.h"


User::User(QGraphicsItem *parent,  int orientation, int velocity) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 50, 50);
    QPixmap pixmap("images/user3.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    QPen pen;
    pen.setWidth(3); // Set the width of the pen to 3 pixels
    pen.setColor(Qt::black); // Set the color of the pen to black, nice and round circle around the user texture
    setPen(pen);

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(rect().width()/2, rect().height() - 0.9*(rect().height()), 10, 10, this);
    QPixmap eye("images/eye5.png");
    eye = eye.scaled(visionPoint->rect().width(), visionPoint->rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush eyeBrush(eye);
    visionPoint->setBrush(eyeBrush);
    visionPoint->setPen(Qt::NoPen);
    visionPoint->setZValue(3);
    QPen eyePen;

    // Magical constant found by trial and error
    speed = 2 + velocity*0.5;
    rotationSpeed = 10.0;
    setTransformOriginPoint(rect().width()/2, rect().height()/2);

    StunnedTimer = new QTimer(this);

    // Timers for the movement using the buttons in the GUI
    ForwardTimer = new QTimer(this);
    ForwardTimer->setInterval(30);
    connect(ForwardTimer, &QTimer::timeout, this, &User::moveForward);

    ClockwiseTimer = new QTimer(this);
    ClockwiseTimer->setInterval(30);
    connect(ClockwiseTimer, &QTimer::timeout, this, &User::rotateClockwise);

    CounterClockwiseTimer = new QTimer(this);
    CounterClockwiseTimer->setInterval(30);
    connect(CounterClockwiseTimer, &QTimer::timeout, this, &User::rotateCounterClockwise);

    // Connect the StunTimerExpired slot to the timeout signal of the StunnedTimer
    connect(StunnedTimer, &QTimer::timeout, this, &User::StunTimerExpired);

    Stunned = false;
    numberOfLives = 3;

    // Timer for the cooldown after being hit (no minus lives in the next second)
    coolDown = new QTimer(this);
    connect(coolDown, &QTimer::timeout, this, &User::endCoolDown);
    isCoolingDown = false;

    // Orientation of the User
    setRotation(orientation);
    hit = false;
}

void User::moveForward() {

    // If the user is stunned, do not move
    if(Stunned) return;

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

    // Check if the new position is within boundaries
    if (newX >= 0 && newX <= 1200 - rect().width() && newY >= 100 && newY <= 700 - rect().height() && !hit) {
        // Apply the movement if within the scene
        setPos(newX, newY);
    }
    hit = false;
    CheckCollisions();
}

void User::rotateClockwise() {
    setRotation(rotation() + rotationSpeed);
}

void User::rotateCounterClockwise() {
    setRotation(rotation() - rotationSpeed);
}

void User::startMovingForward() {
    if(Stunned) return;
    ForwardTimer->start();
}

void User::stopMoving() {
    setFocus();
    ForwardTimer->stop();
}

void User::startRotatingClockwise() {
    ClockwiseTimer->start();
}

void User::startRotatingCounterClockwise() {
    CounterClockwiseTimer->start();
}

void User::stopRotating() {
    setFocus();
    ClockwiseTimer->stop();
    CounterClockwiseTimer->stop();
}

void User::keyPressEvent(QKeyEvent *event) {

    bool forward = false;
    if (event->key() == Qt::Key_Left) {
        // Rotate counterclockwise
        setRotation(rotation() - rotationSpeed);
    } else if (event->key() == Qt::Key_Right) {
        // Rotate clockwise
        setRotation(rotation() + rotationSpeed);
    }

    if (event->key() == Qt::Key_Up && !Stunned) {
        // Move forward in the direction of the vision point
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


        // Check if the new position is within boundaries
        if (newX >= 0 && newX <= 1200 - rect().width() && newY >= 100 && newY <= 700 - rect().height() && !hit && !Stunned) {
            // Apply the movement if within the scene
            setPos(newX, newY);
        }
        hit = false;
        forward = true;
    }
    if (forward) {
        // Check for collisions
        CheckCollisions();
    }
}

void User::CheckCollisions() {
    // Check for collisions with obstacles, using dynamic_cast to check if the item is of type desired
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (QGraphicsItem *item : colliding_items) {
        if (Obstacle const *brick = dynamic_cast<Obstacle *>(item)) {
            // Handle collision with brick
            qDebug() << "Collision with brick detected!";

            spawnStars();  // Spawn stars
            // Stun the user
            Stunned = true;
            StunnedTimer->start(5000); // Stun for 5 seconds
            QPixmap pixmap("images/user3broken.png");
            pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush brush(pixmap);
            setBrush(brush);
            emit stunned();
            return;
        }

        if (Enemy const *enemy = dynamic_cast<Enemy *>(item)) {
            // Handle collision with enemy
            qDebug() << "Collision with enemy detected!";
            hit = true;
            return;
        }
    }
}

void User::spawnStars() {
    // Create stars, 5 of them
    for (int starCount = 0; starCount < 5; ++starCount) {

        // Delay the creation of each star by magical constant which seem to spawn them evenly
        QTimer::singleShot(723 * starCount, this, [this, starCount]() {
            // Values are magical constants, which work with the current size of the User and the star limit
            qreal angleStep = 360.0 / 5;
            qreal radius = 20;
            Star *star = new Star(this);
            qreal angle = qDegreesToRadians(angleStep * starCount);
            qreal starX = rect().center().x() + radius * qCos(angle) - star->rect().width() / 2;
            qreal starY = rect().center().y() + radius * qSin(angle) - star->rect().height() / 2;
            star->setPos(mapToScene(starX, starY));
            scene()->addItem(star);
            stars.append(star);
        });
    }
}

void User::StunTimerExpired() {
    Stunned = false;
    StunnedTimer->stop();
    QPixmap pixmap("images/user3.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    foreach (Star *star, stars) {
        scene()->removeItem(star);
        delete star;
    }
    stars.clear();
}

void User::decreaseLives() {
    if (isCoolingDown) {
        // If the cooldown is active, ignore the signal
        qDebug() << "User is cooling down!";
        return;
    }
    qDebug() << "User hit!";


    if (numberOfLives == 3){
        emit deleteLife3();
    } else if (numberOfLives == 2){
        emit deleteLife2();
    } else if (numberOfLives == 1){
        emit deleteLife1();
    }
    numberOfLives--;
    isCoolingDown = true;
    coolDown->start(1000);
}

void User::endCoolDown() {
    isCoolingDown = false;
    coolDown->stop();
}

void User::switchControl() {
    setFocus();
}

void User::stopAllTimers() {
    remainingStunnedTime = StunnedTimer->remainingTime();
    remainingCoolDownTime = coolDown->remainingTime();
    StunnedTimer->stop();
    ForwardTimer->stop();
    ClockwiseTimer->stop();
    CounterClockwiseTimer->stop();
    coolDown->stop();
}

void User::resumeAllTimers() {
    StunnedTimer->start(remainingStunnedTime);
    ForwardTimer->start();
    ClockwiseTimer->start();
    CounterClockwiseTimer->start();
    coolDown->start(remainingCoolDownTime);
}

User::~User() {
    if (StunnedTimer != nullptr) {
        delete StunnedTimer;
        StunnedTimer = nullptr;
    }
    if (ForwardTimer != nullptr) {
        delete ForwardTimer;
        ForwardTimer = nullptr;
    }
    if (ClockwiseTimer != nullptr) {
        delete ClockwiseTimer;
        ClockwiseTimer = nullptr;
    }
    if (CounterClockwiseTimer != nullptr) {
        delete CounterClockwiseTimer;
        CounterClockwiseTimer = nullptr;
    }
    if (coolDown != nullptr) {
        delete coolDown;
        coolDown = nullptr;
    }
    if (stars.size() > 0) {
        foreach (Star *star, stars) {
            if (star != nullptr) {
                delete star;
                star = nullptr;
            }
        }
    }
    if (visionPoint != nullptr) {
        delete visionPoint;
        visionPoint = nullptr;
    }
}