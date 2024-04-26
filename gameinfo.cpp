//
// Created by marek on 26.04.2024.
//

#include "gameinfo.h"


GameInfo::GameInfo(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QFont font;
    font.setFamily(family);
    font.setPointSize(35);
    setFont(font);
    QColor color(0,255,0);
    setDefaultTextColor(color);
    defaultText = "RUN!";
    setPlainText(defaultText);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameInfo::resetMessage);
}

void GameInfo::updateMessage(const QString& message, const QColor& color, int duration) {
    setPlainText(message);
    setDefaultTextColor(color);
    messageDuration = duration;
    timer->start(messageDuration); // Use the message duration
}

void GameInfo::ouch() {
    updateMessage("OUCH!", QColor(Qt::yellow), 5000); // 5 seconds
}

void GameInfo::damage() {
    updateMessage("SH*T!", QColor(255, 0, 0), 1500); // 1.5 seconds
}

void GameInfo::resetMessage() {
    setPlainText(defaultText);
    setDefaultTextColor(QColor(0, 255, 0)); // Reset the color
    timer->stop();
}