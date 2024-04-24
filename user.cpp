#include "user.h"


User::User(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 100, 100); // Set the size of the ellipse

    QPixmap pixmap("../djkhaled.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(pixmap);

    // Create the vision point
    visionPoint = new QGraphicsEllipseItem(36, 20, 10, 10, this); // Positioned above the center of the User
    visionPoint->setBrush(Qt::red); // Set the color to red

    speed = 10.0;
    rotationSpeed = 10.0;
    setTransformOriginPoint(50, 50);
    StunnedTimer = new QTimer(this);
    connect(StunnedTimer, SIGNAL(timeout()), this, SLOT(StunTimerExpired()));
    Stunned = false;

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
        if (newX >= 0 && newX <= scene()->width() - rect().width() && newY >= 0 && newY <= scene()->height() - rect().height()) {
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

            // Stun the user
            Stunned = true;
            StunnedTimer->start(5000); // Stun for 2 seconds
            QPixmap pixmap("../dj-khaled-tired.png");
            pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush brush(pixmap);
            setBrush(brush);
            return;
        }
    }
}

void User::StunTimerExpired() {
    Stunned = false;
    StunnedTimer->stop();
    QPixmap pixmap("../djkhaled.png");
    pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBrush brush(pixmap);
    setBrush(brush);
}
