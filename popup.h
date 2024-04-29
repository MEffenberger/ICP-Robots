//
// Created by marek on 26.04.2024.
//

#ifndef ICP_POPUP_H
#define ICP_POPUP_H

#include <QGraphicsRectItem>
#include <QObject>
#include "button.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QFontDatabase>
#include <QTimer>
#include <QDebug>
#include <QColor>




class PopUp : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
    PopUp(QGraphicsItem *parent = 0, std::string name = "");
    ~PopUp();
    Button *exitButton;
    Button *restartButton;
    Button *resumeButton;
    Button *mainMenuButton;
private:
    std::string name;
    QGraphicsTextItem *createTextItem(const QString& text, const QString& fontFamily, int fontSize, const QColor& color);
public slots:
//    void exit();
//    void restart();
//    void resume();
//    void mainMenu();
    void show();
    void hide();
signals:
    void pauseTimers();
};


#endif //ICP_POPUP_H
