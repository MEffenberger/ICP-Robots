/**
 * @file timer.h
 * @brief Timer class header file
 * @version 1.0
 * @details This class is responsible for creating a timer that counts up to a certain limit
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */


#ifndef ICP_TIMER_H
#define ICP_TIMER_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include <QFontDatabase>
#include <QFont>
#include <QColor>


/**
 * @brief Timer class, inherits from QGraphicsTextItem
 */
class Timer : public QGraphicsTextItem
{
Q_OBJECT

public:

    /**
     * @brief Timer constructor
     * @param parent Parent QGraphicsItem
     * @param timeL Time limit of the timer
     */
    Timer(QGraphicsItem *parent = 0, int timeL = 60);

    /**
     * @brief Timer destructor
     */
    ~Timer();

private:

    /** Timer */
    QTimer *timer;

    /** Time */
    int time;

    /** Time limit */
    int timeLimit;

    /** Remaining time */
    int internalTimer;

signals:

    /**
     * @brief Signal emitted when the time is up, victory popup is shown
     */
    void timeIsUp();

public slots:

    /**
     * @brief Update the timer
     */
    void updateTimer();

    /**
     * @brief Stop the timer
     */
    void stopTimer();

    /**
     * @brief Continue the timer
     */
    void continueTimer();
};






#endif //ICP_TIMER_H
