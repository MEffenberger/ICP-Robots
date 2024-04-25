//
// Created by marek on 25.04.2024.
//

#include "horizontalbar.h"


HorizontalLowerBar::HorizontalLowerBar(User *user) {
    width = 1200;
    height = 100;
    setRect(0, 0, width, height);
    QPixmap pixmap("../images/bar.png");
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    setPos(0, 700);

    // Initialize the buttons with their respective images
    ForwardButton = new Button(QPixmap("../images/forward.png"), "Forward",this);
    ClockwiseButton = new Button(QPixmap("../images/clockwise.png"),"Clockwise", this);
    CounterClockwiseButton = new Button(QPixmap("../images/anticlockwise.png"),"CounterClockwise", this);

    // Position the buttons
    qreal offset = 12.5;
    ForwardButton->setPos(width - ForwardButton->boundingRect().width() - offset - 10, offset);
    ClockwiseButton->setPos(width - ClockwiseButton->boundingRect().width() - ForwardButton->boundingRect().width() - offset - 15, offset);
    CounterClockwiseButton->setPos(width - ClockwiseButton->boundingRect().width() - ForwardButton->boundingRect().width() - CounterClockwiseButton->boundingRect().width() - offset - 20, offset);

    // Connect the buttons to the User actions
    connect(ForwardButton, &Button::pressed, user, &User::moveForward);
    connect(ClockwiseButton, &Button::pressed, user, &User::rotateClockwise);
    connect(CounterClockwiseButton, &Button::pressed, user, &User::rotateCounterClockwise);

    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QGraphicsTextItem *text = new QGraphicsTextItem("Epic Robot Survivor", this);
    QFont font;
    font.setFamily(family);
    font.setPointSize(37);
    text->setFont(font);
    QColor color(0,255,0);
    text->setDefaultTextColor(color);
    text->setPos(20, 12.5);
}

HorizontalUpperBar::HorizontalUpperBar() {
    width = 1200;
    height = 100;
    setRect(0, 0, width, height);
    QPixmap pixmap("../images/bar.png");
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    setPos(0, 0);

//    // Initialize the timer and pause buttons with their respective images
//    Timer = new Button(QPixmap("../images/timer.png"));
//    Pause = new Button(QPixmap("../images/pause.png"));
//
//    // Add the buttons to the scene
//    scene()->addItem(Timer);
//    scene()->addItem(Pause);
//
//    // Position the buttons
//    Timer->setPos(x + width - Timer->boundingRect().width(), y);
//    Pause->setPos(x + width - Pause->boundingRect().width() - Timer->boundingRect().width(), y);
}