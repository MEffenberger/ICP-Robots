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
    connect(ForwardButton, &Button::pressed, user, &User::startMovingForward);
    connect(ClockwiseButton, &Button::pressed, user, &User::startRotatingClockwise);
    connect(CounterClockwiseButton, &Button::pressed, user, &User::startRotatingCounterClockwise);
    connect(ForwardButton, &Button::released, user, &User::stopMoving);
    connect(ClockwiseButton, &Button::released, user, &User::stopRotating);
    connect(CounterClockwiseButton, &Button::released, user, &User::stopRotating);

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

HorizontalUpperBar::HorizontalUpperBar(User *user) {
    width = 1200;
    height = 100;
    setRect(0, 0, width, height);
    QPixmap pixmap("../images/bar.png");
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    setPos(0, 0);


    Heart1 = new Heart(this);
    Heart2 = new Heart(this);
    Heart3 = new Heart(this);

    Heart1->setPos(22.5, 12.5);
    Heart2->setPos(102.5, 12.5);
    Heart3->setPos(177.5, 12.5);

    connect(user, &User::deleteLife1, Heart1, &Heart::setDead);
    connect(user, &User::deleteLife2, Heart2, &Heart::setDead);
    connect(user, &User::deleteLife3, Heart3, &Heart::setDead);

    gameInfo = new GameInfo(this);
    gameInfo->setPos(810, 12.5);

    connect(user, &User::stunned, gameInfo, &GameInfo::ouch);
    connect(user, &User::deleteLife1, gameInfo, &GameInfo::damage);
    connect(user, &User::deleteLife2, gameInfo, &GameInfo::damage);
    connect(user, &User::deleteLife3, gameInfo, &GameInfo::damage);

    timer = new Timer(this);
    timer->setPos(1000, 17);

    QPixmap pixmap2("../images/pause.png");
    pixmap2 = pixmap2.scaled(75, 75, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pauseButton = new Button(pixmap2, "Pause", this);
    pauseButton->setPos(562.5, 12.5);

}