/**
 * @file horizontalbar.h
 * @brief HorizontalBar classes (upper, lower) header file
 * @version 1.0
 * @details This class is responsible for creating the horizontal bars in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#ifndef ICP_HORIZONTALBAR_H
#define ICP_HORIZONTALBAR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include "button.h"
#include "user.h"
#include <QGraphicsItem>
#include <QObject>
#include <QPen>
#include <QGraphicsTextItem>
#include <QFontDatabase>
#include "heart.h"
#include "gameinfo.h"
#include "timer.h"


/**
 * @brief HorizontalUpperBar class, inherits from QObject and QGraphicsRectItem
 */
class HorizontalUpperBar : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:

    /**
     * @brief HorizontalUpperBar constructor
     * @param user User object
     * @param timeLimit Time limit for the game
     */
    HorizontalUpperBar(User *user, int timeLimit);

    /**
     * @brief HorizontalUpperBar destructor
     */
    ~HorizontalUpperBar();

    /** Pause button */
    Button *pauseButton;

    /** Timer */
    Timer *timer;

private:

    /** Width of the bar */
    int width{};

    /** Height of the bar */
    int height{};

    /** Heart icons */
    Heart *Heart1;
    Heart *Heart2;
    Heart *Heart3;

    /** GameInfo text box */
    GameInfo *gameInfo;

};


/**
 * @brief HorizontalLowerBar class, inherits from QObject and QGraphicsRectItem
 */
class HorizontalLowerBar : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:

    /**
     * @brief HorizontalLowerBar constructor
     * @param user User object
     */
    HorizontalLowerBar(User *user);

    /**
     * @brief HorizontalLowerBar destructor
     */
    ~HorizontalLowerBar();

    /** Autopilot rectangle */
    QGraphicsRectItem *Autopilot;

private:

    /** Width of the bar */
    int width{};

    /** Height of the bar */
    int height{};

    /** Forward button */
    Button *ForwardButton;

    /** Clockwise button */
    Button *ClockwiseButton;

    /** Counter-clockwise button */
    Button *CounterClockwiseButton;

    /** Keyboard button */
    Button *KeyboardButton;

    /** User object */
    User *userPtr;

protected:

    /**
     * @brief Mouse release event
     * @param event QGraphicsSceneMouseEvent
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};


#endif //ICP_HORIZONTALBAR_H
