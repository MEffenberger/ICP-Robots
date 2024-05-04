/**
 * @file timer.cpp
 * @brief Timer class implementation file
 * @version 1.0
 * @details This class is responsible for a timer that counts up to a certain limit
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */


#include "timer.h"


Timer::Timer(QGraphicsItem *parent, int timeL) : QGraphicsTextItem(parent)
{

    // Load font and set it
    int fontId = QFontDatabase::addApplicationFont("Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font;
    font.setFamily(family);
    font.setPointSize(30);
    setFont(font);
    QColor color(0,255,0);
    setDefaultTextColor(color);
    time = 0;
    timeLimit = timeL;

    // Format is "time / timeLimit"
    setPlainText(QString::number(time) + QString(" / ") + QString::number(timeLimit));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::updateTimer);
    timer->start(1000);
}


void Timer::updateTimer() {
    // Update the timer and change the color to red if the time is running out
    time++;
    if (timeLimit - 3 <= time) {
        setDefaultTextColor(QColor(255, 0, 0));
    }
    setPlainText(QString::number(time) + QString(" / ") + QString::number(timeLimit));
    timer->start(1000);
    if (time == timeLimit) {
        timer->stop();
        emit timeIsUp();
    }
}

void Timer::stopTimer() {
    // Stop the timer and save the remaining time
    internalTimer = timer->remainingTime();
    timer->stop();
}

void Timer::continueTimer() {
    // Continue the timer with the remaining time
    timer->start(internalTimer);
}

Timer::~Timer() {
    if (timer != nullptr){
    delete timer;
    timer = nullptr;
    }
}
