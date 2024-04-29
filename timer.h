//
// Created by marek on 26.04.2024.
//

#ifndef ICP_TIMER_H
#define ICP_TIMER_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include <QFontDatabase>
#include <QFont>
#include <QColor>

class Timer : public QGraphicsTextItem
{
Q_OBJECT

public:

    Timer(QGraphicsItem *parent = 0, int timeL = 60);
    ~Timer();

private:

    QTimer *timer;
    int time;
    int timeLimit;
    int internalTimer;

signals:
    void timeIsUp();

public slots:
    void resetTimer();
    void pauseTimer();
    void stopTimer();
    void continueTimer();

};






#endif //ICP_TIMER_H
