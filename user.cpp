#include "user.h"


User::User(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 75, 75); // Set the size of the ellipse

    QPixmap pixmap("../images/user3.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
    QPen pen;
    pen.setWidth(3); // Set the width of the pen to 3 pixels
    pen.setColor(Qt::black); // Set the color of the pen to black
    setPen(pen);

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(37.5, 56.25, 10, 10, this); // Positioned above the center of the User
    visionPoint->setBrush(Qt::red);

    speed = 10.0;
    rotationSpeed = 10.0;
    setTransformOriginPoint(37.5, 37.5);
    StunnedTimer = new QTimer(this);
    connect(StunnedTimer, SIGNAL(timeout()), this, SLOT(StunTimerExpired()));
    Stunned = false;

}

void User::moveForward() {
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
    if (newX >= 0 && newX <= 1200 - rect().width() && newY >= 100 && newY <= 700 - rect().height()) {
        // Apply the movement if within the scene
        setPos(newX, newY);
    }
    CheckCollisions();
}

void User::rotateClockwise() {
    setRotation(rotation() + rotationSpeed);
}

void User::rotateCounterClockwise() {
    setRotation(rotation() - rotationSpeed);
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
        if (newX >= 0 && newX <= 1200 - rect().width() && newY >= 100 && newY <= 700 - rect().height()) {
            // Apply the movement if within the scene
            setPos(newX, newY);
        }
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
           // QSound::play("../anotherone.wav");
            QPixmap pixmap("../images/user3broken.png");
            pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush brush(pixmap);
            setBrush(brush);
            return;
        }
    }
}

void User::spawnStars(int starCount) {
    if (starCount < 5) {
        QTimer::singleShot(723, this, [this, starCount]() {
            qreal angleStep = 360.0 / 5;  // Divide a full circle into 5 steps (for 5 stars)
            qreal radius = 50;  // Adjust this radius if needed to spread out the stars

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

void User::aaa() {
    qDebug() << "aaa";
}