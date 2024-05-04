/**
 * @file star.h
 * @brief Star class header file
 * @version 1.0
 * @details This class is responsible for creating and moving little stars when the user is stunned
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */


#ifndef ICP_STAR_H
#define ICP_STAR_H

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <QtMath>


/**
 * @brief Star class, inherits from QObject and QGraphicsEllipseItem
 */
class Star : public QObject, public QGraphicsEllipseItem {
Q_OBJECT
public:

    /**
     * @brief Star constructor
     * @param parent Parent QGraphicsItem
     */
    Star(QGraphicsItem *parent = 0);

    /**
     * @brief Star destructor
     */
    ~Star() = default;

public slots:

    /**
     * @brief Move the star
     */
    void move();
};


#endif //ICP_STAR_H
