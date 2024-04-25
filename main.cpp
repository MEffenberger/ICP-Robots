#include "mainwindow.h"
#include "user.h"
#include "obstacle.h"
#include "enemy.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a scene
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1200, 800);
    QPixmap bg("../background.png");
    bg = bg.scaled(scene.width(), scene.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene.setBackgroundBrush(bg);

    // Create an instance of User
    User *user = new User();

    // Add the user to the scene
    scene.addItem(user);
    user->setFlag(QGraphicsItem::ItemIsFocusable);
    user->setFocus();
    user->setPos(scene.sceneRect().center());

    Enemy *enemy = new Enemy();
    scene.addItem(enemy);
    enemy->setPos(500, 500);
    QTimer::singleShot(3000, enemy, &Enemy::startAutonomousMovement);

    Enemy *enemy2 = new Enemy();
    scene.addItem(enemy2);
    enemy2->setPos(700, 700);
    QTimer::singleShot(3000, enemy2, &Enemy::startAutonomousMovement);


    Obstacle *brick = new Obstacle();
    Obstacle *brick2 = new Obstacle();
    Obstacle *brick3 = new Obstacle();
    Obstacle *brick4 = new Obstacle();
    scene.addItem(brick);
    brick->setPos(300, 300);
    scene.addItem(brick2);
    brick2->setPos(200, 200);
    scene.addItem(brick3);
    brick3->setPos(400, 400);
    scene.addItem(brick4);
    brick4->setPos(1000, 1000);


    // Create a view to visualize the scene
    QGraphicsView view(&scene);

    view.setFixedSize(1200, 800); //
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Show the view
    view.show();

    return a.exec();
}