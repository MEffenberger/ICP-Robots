#include "user.h"
#include "enemy.h"


User::User(QGraphicsItem *parent,  int orientation, int velocity) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 50, 50); // Set the size of the ellipse

    QPixmap pixmap("../images/user3.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    QPen pen;
    pen.setWidth(3); // Set the width of the pen to 3 pixels
    pen.setColor(Qt::black); // Set the color of the pen to black
    setPen(pen);

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(rect().width()/2, rect().height()- 0.8*(rect().height()), 10, 10, this); // Positioned above the center of the User
    QPixmap eye("../images/eye4.png");
    eye = eye.scaled(visionPoint->rect().width(), visionPoint->rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush eyeBrush(eye);
    visionPoint->setBrush(eyeBrush);
    visionPoint->setPen(Qt::NoPen); // No border
    visionPoint->setZValue(3); // Set the z value to 1 so it's drawn on top of the vision field
    QPen eyePen;



    speed = 2 + velocity*0.5;
    rotationSpeed = 10.0;
    setTransformOriginPoint(rect().width()/2, rect().height()/2);

    StunnedTimer = new QTimer(this);

    ForwardTimer = new QTimer(this);
    ForwardTimer->setInterval(30); // Adjust this value as needed
    connect(ForwardTimer, &QTimer::timeout, this, &User::moveForward);

    ClockwiseTimer = new QTimer(this);
    ClockwiseTimer->setInterval(30); // Adjust this value as needed
    connect(ClockwiseTimer, &QTimer::timeout, this, &User::rotateClockwise);

    CounterClockwiseTimer = new QTimer(this);
    CounterClockwiseTimer->setInterval(30); // Adjust this value as needed
    connect(CounterClockwiseTimer, &QTimer::timeout, this, &User::rotateCounterClockwise);

    connect(StunnedTimer, SIGNAL(timeout()), this, SLOT(StunTimerExpired()));
    Stunned = false;
    numberOfLives = 3;

    coolDown = new QTimer(this);
    connect(coolDown, &QTimer::timeout, this, &User::endCoolDown); // Connect the timer's timeout signal to the endCooldown slot
    isCoolingDown = false;

    setRotation(orientation);
    hit = false;
}

void User::moveForward() {

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
    // Check for collisions with obstacles
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (QGraphicsItem *item : colliding_items) {
        if (Obstacle const *brick = dynamic_cast<Obstacle *>(item)) {
            // Handle collision with brick
            qDebug() << "Collision with brick detected!";

            spawnStars(0);  // Spawn stars
            // Stun the user
            Stunned = true;
            StunnedTimer->start(5000); // Stun for 2 seconds
            QPixmap pixmap("../images/user3broken.png");
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

void User::spawnStars(int starCount) {
    if (starCount < 5) {
        QTimer::singleShot(723, this, [this, starCount]() {
            qreal angleStep = 360.0 / 5;  // Divide a full circle into 5 steps (for 5 stars)
            qreal radius = 20;  // Adjust this radius if needed to spread out the stars

            Star *star = new Star(this);  // New instance creation
            qreal angle = qDegreesToRadians(angleStep * starCount);
            qreal starX = rect().center().x() + radius * qCos(angle) - star->rect().width() / 2;
            qreal starY = rect().center().y() + radius * qSin(angle) - star->rect().height() / 2;
            star->setPos(mapToScene(starX, starY));
            scene()->addItem(star);
            stars.append(star);

            // Recursively call this function to spawn the next star
            spawnStars(starCount + 1);
        });
    }
}

void User::StunTimerExpired() {
    Stunned = false;
    StunnedTimer->stop();
    QPixmap pixmap("../images/user3.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    foreach (Star *star, stars) {
        scene()->removeItem(star);  // Remove from scene
        delete star;                // Delete the object
    }
    stars.clear();  // Clear the list
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
        die();
    }
    numberOfLives--;
    isCoolingDown = true;
    coolDown->start(1000);
}

void User::die() {
    // Handle user death
    qDebug() << "User died!";
    // Implement game over logic here
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