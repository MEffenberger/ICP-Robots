#include "mainwindow.h"
#include "user.h"
#include "obstacle.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a scene
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1200, 800);

    // Create an instance of User
    User *user = new User();

    // Add the user to the scene
    scene.addItem(user);
    user->setFlag(QGraphicsItem::ItemIsFocusable);
    user->setFocus();


    Obstacle *brick = new Obstacle();
    Obstacle *brick2 = new Obstacle();

    scene.addItem(brick);
    scene.addItem(user);
    user->setPos(scene.sceneRect().center());
    brick->setPos(300, 300);
    scene.addItem(brick2);
    brick2->setPos(200, 200);

    // Create a view to visualize the scene
    QGraphicsView view(&scene);

    view.setFixedSize(1200, 800); //
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Show the view
    view.show();

    return a.exec();
}