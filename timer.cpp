//
// Created by marek on 26.04.2024.
//

#include "timer.h"


Timer::Timer(QGraphicsItem *parent, int timeL) : QGraphicsTextItem(parent)
{
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QFont font;
    font.setFamily(family);
    font.setPointSize(30);
    setFont(font);
    QColor color(0,255,0);
    setDefaultTextColor(color);
    time = 0;
    timeLimit = timeL;
    setPlainText(QString::number(time) + QString(" / ") + QString::number(timeLimit));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::pauseTimer);
    timer->start(1000);
}

void Timer::resetTimer() {
    time = 0;
    setPlainText(QString::number(time) + QString(" / ") + QString::number(timeLimit));
    timer->start(1000);
}

void Timer::pauseTimer() {
    time++;

    if (timeLimit - 3 <= time) {
        setDefaultTextColor(QColor(255, 0, 0));
    }

    setPlainText(QString::number(time) + QString(" / ") + QString::number(timeLimit));
    if (time == timeLimit) {
        timer->stop();
        emit timeIsUp();
    }
}

void Timer::stopTimer() {
    internalTimer = timer->remainingTime();
    timer->stop();
}

void Timer::continueTimer() {
    timer->start(internalTimer);
}
