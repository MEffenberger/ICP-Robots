#include "mainwindow.h"
#include "user.h"
#include "obstacle.h"
#include "enemy.h"
#include "horizontalbar.h"
#include "popup.h"
#include "mapwindow.h"
#include "gamemaster.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameMaster gameMaster;
    gameMaster.run();
//    MainWindow w;
//    w.show();
//    QGraphicsScene scene;
//    User *user = new User();
//    HorizontalLowerBar *lowerBar = new HorizontalLowerBar(user);
//    HorizontalUpperBar *upperBar = new HorizontalUpperBar(user);
//
//    scene.setSceneRect(0, 0, 1200, 800);
//
//    QPixmap bg("../images/bg.png");
//    bg = bg.scaled(scene.width(), scene.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    scene.setBackgroundBrush(bg);
//
//    scene.addItem(lowerBar);
//    lowerBar->setPos(0, 700);
//    scene.addItem(upperBar);
//    upperBar->setPos(0, 0);
//
//    PopUp *popup = new PopUp(nullptr, "gameover");
//    scene.addItem(popup);
//    popup->setPos(scene.width()/2 - popup->rect().width()/2, scene.height()/2 - popup->rect().height()/2);
//
//
//    // Add the user to the scene
//    scene.addItem(user);
//    user->setFlag(QGraphicsItem::ItemIsFocusable); // construktor?
//    user->setFocus();
//    user->setPos(scene.sceneRect().center());
//
//    Enemy *enemy = new Enemy(nullptr, user);
//    scene.addItem(enemy);
//    enemy->setPos(500, 500);
//    //QTimer::singleShot(3000, enemy, &Enemy::startAutonomousMovement);
//
//    Enemy *enemy2 = new Enemy(nullptr, user);
//    scene.addItem(enemy2);
//    enemy2->setPos(1000, 250);
//    //QTimer::singleShot(3000, enemy2, &Enemy::startAutonomousMovement);
//
//
//    Obstacle *brick = new Obstacle();
//    Obstacle *brick2 = new Obstacle();
//    Obstacle *brick3 = new Obstacle();
//    Obstacle *brick4 = new Obstacle();
//    scene.addItem(brick);
//    brick->setPos(300, 300);
//    scene.addItem(brick2);
//    brick2->setPos(200, 200);
//    scene.addItem(brick3);
//    brick3->setPos(400, 400);
//    scene.addItem(brick4);
//    brick4->setPos(1000, 300);
//
//
//    // Create a view to visualize the scene
//    QGraphicsView view(&scene);
//
//    view.setFixedSize(1200, 800); //
//    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view.setFocusPolicy(Qt::StrongFocus);
//
//    QSound::play("../sounds/missionimpossible.wav");
//    // Show the view
//    view.show();

    return a.exec();
}