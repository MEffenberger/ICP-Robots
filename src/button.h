/**
 * @file button.h
 * @brief Button class header file
 * @version 1.0
 * @details This class is responsible for creating buttons in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#ifndef ICP_BUTTON_H
#define ICP_BUTTON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <QObject>
#include <QPen>
#include <QTimer>
#include <QDebug>


/**
 * @brief Button class, inherits from QObject and QGraphicsRectItem
 */
class Button : public QObject, public QGraphicsRectItem {

    Q_OBJECT

public:

    /**
     * @brief Button constructor
     * @param pixmap QPixmap object
     * @param name Name of the button
     * @param parent Parent QGraphicsItem
     * @param x X coordinate
     * @param y Y coordinate
     */
    explicit Button(const QPixmap& pixmap, std::string name, QGraphicsItem *parent = 0, qreal x = 0, qreal y = 0);

    /**
     * @brief Button destructor
     */
    ~Button() = default;

signals:

    /**
     * @brief Signal emitted when the button is pressed
     */
    void pressed();

    /**
     * @brief Signal emitted when the button is released
     */
    void released();

    /**
     * @brief Signal emitted when the button is released and the autopilot rectangle contains the mouse position
     */
    void autoPilot();

protected:

    /**
     * @brief Mouse press event
     * @param event QGraphicsSceneMouseEvent object
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Mouse release event
     * @param event QGraphicsSceneMouseEvent object
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:

    /** Name of the button (used for debugging and various signals) */
    std::string name;

    /** Rectangle for the autopilot button (a bit above the forward button) */
    QRectF autoPilotPosition;

public slots:

    /**
     * @brief Set the border width of the button
     * @param width Width of the border
     */
    void setBorderWidth(int width);
};


#endif //ICP_BUTTON_H
