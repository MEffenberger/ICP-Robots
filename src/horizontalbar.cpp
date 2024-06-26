/**
 * @file horizontalbar.cpp
 * @brief HorizontalBar classes (upper, lower) implementation file
 * @version 1.0
 * @details This class is responsible for creating the horizontal bars in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#include "horizontalbar.h"



HorizontalLowerBar::HorizontalLowerBar(User *user) {
    width = 1200;
    height = 100;
    setRect(0, 0, width, height);
    QPixmap pixmap("images/bar.png");
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    setPos(0, 700);
    userPtr = user;

    // Initialize the buttons with their respective images
    ForwardButton = new Button(QPixmap("images/forward.png"), "Forward",this, 75, 75);
    ClockwiseButton = new Button(QPixmap("images/clockwise.png"),"Clockwise", this, 75, 75);
    CounterClockwiseButton = new Button(QPixmap("images/anticlockwise.png"),"CounterClockwise", this, 75, 75);

    // Position the buttons
    qreal offset = 12.5;
    ForwardButton->setPos(width - ForwardButton->boundingRect().width() - offset - 10, offset);
    ClockwiseButton->setPos(width - ClockwiseButton->boundingRect().width() - ForwardButton->boundingRect().width() - offset - 15, offset);
    CounterClockwiseButton->setPos(width - ClockwiseButton->boundingRect().width() - ForwardButton->boundingRect().width() - CounterClockwiseButton->boundingRect().width() - offset - 20, offset);

    // Connect the buttons to the User actions
    connect(ForwardButton, &Button::pressed, user, &User::startMovingForward);
    connect(ForwardButton, &Button::autoPilot, user, &User::switchControl);

    connect(ClockwiseButton, &Button::pressed, user, &User::startRotatingClockwise);
    connect(CounterClockwiseButton, &Button::pressed, user, &User::startRotatingCounterClockwise);
    connect(ForwardButton, &Button::released, user, &User::stopMoving);
    connect(ClockwiseButton, &Button::released, user, &User::stopRotating);
    connect(CounterClockwiseButton, &Button::released, user, &User::stopRotating);

    KeyboardButton = new Button(QPixmap("images/keyboard.png"), "Keyboard", this, 75, 75);
    KeyboardButton->setPos(850, 12.5);
    connect(KeyboardButton, &Button::pressed, user, &User::switchControl);


    int fontId = QFontDatabase::addApplicationFont("Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);


    // Add text, simply design purposes
    QGraphicsTextItem *text = new QGraphicsTextItem("Epic Robot Survival", this);
    QFont font;
    font.setFamily(family);
    font.setPointSize(37);
    text->setFont(font);
    QColor color(0,255,0);
    text->setDefaultTextColor(color);
    text->setPos(20, 12.5);

    // Add the autopilot button -> the real "implementation" of the autopilot is in the Button class
    Autopilot = new QGraphicsRectItem(0, 0, 75, 40, this);
    Autopilot->setPos(width - ForwardButton->boundingRect().width() - offset - 10, -40);
    QPixmap pixmap2 = pixmap.scaled(Autopilot->rect().width(), Autopilot->rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    Autopilot->setBrush(pixmap);
    Autopilot->setOpacity(0.7);
    Autopilot->setPen(QPen(Qt::NoPen));
    Autopilot->setZValue(15);

    // Add text to the autopilot button
    QGraphicsTextItem *text1 = new QGraphicsTextItem("Release For", Autopilot);
    font.setPointSize(7);
    text1->setFont(font);
    text1->setDefaultTextColor(QColor(0, 255, 0));
    text1->setPos(5, 0);
    QGraphicsTextItem *text2 = new QGraphicsTextItem("Autopilot", Autopilot);
    text2->setFont(font);
    text2->setDefaultTextColor(QColor(0, 0, 255));
    text2->setPos(10, text1->boundingRect().height() - 5);

}

HorizontalLowerBar::~HorizontalLowerBar() {
    if (ForwardButton != nullptr){
        delete ForwardButton;
        ForwardButton = nullptr;
    }
    if (ClockwiseButton != nullptr) {
        delete ClockwiseButton;
        ClockwiseButton = nullptr;
    }
    if (CounterClockwiseButton != nullptr) {
        delete CounterClockwiseButton;
        CounterClockwiseButton = nullptr;
    }
    if (KeyboardButton != nullptr) {
        delete KeyboardButton;
        KeyboardButton = nullptr;
    }
    if (Autopilot != nullptr) {
        delete Autopilot;
        Autopilot = nullptr;
    }
}

void HorizontalLowerBar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (Autopilot->contains(event->pos())) {
        qDebug() << "Autopilot button is released";
        emit userPtr->switchControl();
    }
}




HorizontalUpperBar::HorizontalUpperBar(User *user, int timeLimit) {
    // Set the width and height of the bar
    width = 1200;
    height = 100;
    setRect(0, 0, width, height);
    QPixmap pixmap("images/bar.png");
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setBrush(pixmap);
    setPos(0, 0);

    // Create the hearts
    Heart1 = new Heart(this);
    Heart2 = new Heart(this);
    Heart3 = new Heart(this);

    // Position the hearts
    Heart1->setPos(22.5, 12.5);
    Heart2->setPos(102.5, 12.5);
    Heart3->setPos(177.5, 12.5);

    // Connect the hearts to the User actions
    connect(user, &User::deleteLife1, Heart1, &Heart::setDead);
    connect(user, &User::deleteLife2, Heart2, &Heart::setDead);
    connect(user, &User::deleteLife3, Heart3, &Heart::setDead);

    gameInfo = new GameInfo(this);
    gameInfo->setPos(730, 12.5);

    // Connect the GameInfo to the User actions
    connect(user, &User::stunned, gameInfo, &GameInfo::ouch);
    connect(user, &User::deleteLife1, gameInfo, &GameInfo::damage);
    connect(user, &User::deleteLife2, gameInfo, &GameInfo::damage);
    connect(user, &User::deleteLife3, gameInfo, &GameInfo::damage);

    // Create the timer for the game
    timer = new Timer(this, timeLimit);
    timer->setPos(950, 17);

    // Create the pause button
    QPixmap pixmap2("images/pause.png");
    pixmap2 = pixmap2.scaled(75, 75, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pauseButton = new Button(pixmap2, "Pause", this, 75, 75);
    pauseButton->setPos(562.5, 12.5);

}

HorizontalUpperBar::~HorizontalUpperBar() {
    if (Heart1 != nullptr) {
        delete Heart1;
        Heart1 = nullptr;
    }
    if (Heart2 != nullptr) {
        delete Heart2;
        Heart2 = nullptr;
    }
    if (Heart3 != nullptr) {
        delete Heart3;
        Heart3 = nullptr;
    }
    if (gameInfo != nullptr) {
        delete gameInfo;
        gameInfo = nullptr;
    }
    if (timer != nullptr) {
        delete timer;
        timer = nullptr;
    }
    if (pauseButton != nullptr) {
        delete pauseButton;
        pauseButton = nullptr;
    }
}
