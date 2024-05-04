/**
 * @file popup.h
 * @brief Popup class header file
 * @version 1.0
 * @details This class is responsible for creating the three popups in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

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


/**
 * @brief Popup class, inherits from QObject and QGraphicsRectItem
 */
class PopUp : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:

    /**
     * @brief Popup constructor
     * @param parent Parent QGraphicsItem
     * @param name Name of the popup
     */
    PopUp(QGraphicsItem *parent = 0, std::string name = "");

    /**
     * @brief Popup destructor
     */
    ~PopUp();

    /** Exit button */
    Button *exitButton;

    /** Restart button */
    Button *restartButton;

    /** Resume button (in victory/ gameover screen does nothing)*/
    Button *resumeButton;

    /** Main menu button */
    Button *mainMenuButton;

private:

    /** Name of the popup */
    std::string name;

    /**
     * @brief Creates a text item, used for simplifying the code
     * @param text Text of the item
     * @param fontFamily Font family
     * @param fontSize Font size
     * @param color Color of the text
     * @return QGraphicsTextItem
     */
    QGraphicsTextItem *createTextItem(const QString& text, const QString& fontFamily, int fontSize, const QColor& color);

public slots:

    /**
     * @brief Show the popup
     */
    void show();

    /**
     * @brief Hide the popup
     */
    void hide();

signals:

    /**
     * @brief Pause the timers
     */
    void pauseTimers();
};


#endif //ICP_POPUP_H
