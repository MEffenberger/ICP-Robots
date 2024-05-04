/**
 * @file popup.cpp
 * @brief Popup class implementation file
 * @version 1.0
 * @details This class is responsible for creating the three popups in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */


#include "popup.h"


PopUp::PopUp(QGraphicsItem *parent, std::string name) : QGraphicsRectItem(parent) {

    // Set the size of the rectangle
    setRect(0, 0, 400, 500);
    setBrush(QBrush(QColor(0, 0, 0, 200)));
    setPen(QPen(Qt::NoPen));

    // Hide the popup by default
    hide();

    // Add the Orbitron font
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QGraphicsTextItem *text;

    // Except for Pause, the resume button does nothing
    resumeButton = new Button(QPixmap("../images/bar.png"), "switch", this, 400, 125);
    resumeButton->setPos(0, 0);
    resumeButton->setBorderWidth(5);
    if (name == "gameover") {
        text = createTextItem("Game Over", family, 37, QColor(255, 0, 0));
    } else if (name == "paused") {
        text = createTextItem("Resume", family, 37, QColor(0, 255, 0));
    } else if (name == "win") {
        text = createTextItem("You Win", family, 37, QColor(255, 250, 205));
    }
    // The X coordinate shall be aligned to the center of the popup
    text->setPos(200 - text->boundingRect().width() / 2, 25);


    restartButton = new Button(QPixmap("../images/bar.png"), "restart", this, 400, 125);
    restartButton->setPos(0, 125);
    restartButton->setBorderWidth(5);
    text = createTextItem("Restart", family, 37, QColor(0, 255, 0));
    text->setPos(200 - text->boundingRect().width() / 2, 125 + 25);


    mainMenuButton = new Button(QPixmap("../images/bar.png"), "mainmenu", this, 400, 125);
    mainMenuButton->setPos(0, 250);
    mainMenuButton->setBorderWidth(5);
    text = createTextItem("Main Menu", family, 37, QColor(0, 255, 0));
    text->setPos(200 - text->boundingRect().width() / 2, 250 + 25);


    exitButton = new Button(QPixmap("../images/bar.png"), "Exit", this, 400, 125);
    exitButton->setPos(0, 375);
    exitButton->setBorderWidth(5);
    text = createTextItem("Exit", family, 37, QColor(0, 255, 0));
    text->setPos(200 - text->boundingRect().width() / 2, 375 + 25);
}


void PopUp::show() {
    // If the window is displayed the pauseTimers signal is emitted, GameMaster class is connected to this signal
    emit pauseTimers();
    // The popup is displayed on top of everything
    this->setZValue(100);
    setVisible(true);
    clearFocus();
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}


void PopUp::hide() {
    // Hide the popup
    setVisible(false);
    clearFocus();
    setFlag(QGraphicsItem::ItemIsFocusable, false);
}


QGraphicsTextItem* PopUp::createTextItem(const QString& text, const QString& fontFamily, int fontSize, const QColor& color) {
    QGraphicsTextItem *item = new QGraphicsTextItem(text, this);
    QFont font;
    font.setFamily(fontFamily);
    font.setPointSize(fontSize);
    item->setFont(font);
    item->setDefaultTextColor(color);
    return item;
}


PopUp::~PopUp() {
    if (exitButton != nullptr) {
        delete exitButton;
        exitButton = nullptr;
    }
    if (restartButton != nullptr) {
        delete restartButton;
        restartButton = nullptr;
    }
    if (resumeButton != nullptr) {
        delete resumeButton;
        resumeButton = nullptr;
    }
    if (mainMenuButton != nullptr) {
        delete mainMenuButton;
        mainMenuButton = nullptr;
    }
}