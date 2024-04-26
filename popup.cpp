//
// Created by marek on 26.04.2024.
//

#include "popup.h"


PopUp::PopUp(QGraphicsItem *parent, std::string name) : QGraphicsRectItem(parent) {
    setRect(0, 0, 400, 500);
    setBrush(QBrush(QColor(0, 0, 0, 200)));
    setPen(QPen(Qt::NoPen));
    //setPos(200, 200);
    show();
    int fontId = QFontDatabase::addApplicationFont("../Orbitron/static/Orbitron-ExtraBold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    resumeButton = new Button(QPixmap(":/images/bar.png"), "switch", this, 100, 125);
    resumeButton->setPos(0, 0);
   // connect(exitButton, &Button::pressed, this, &popup::exit);
    QGraphicsTextItem *text;
    if (name == "gameover") {
        text = createTextItem("Game Over", family, 37, QColor(255, 0, 0), 100, 125);
    } else if (name == "paused") {
        text = createTextItem("Paused", family, 37, QColor(0, 255, 0), 100, 125);
    } else if (name == "win") {
        text = createTextItem("You Win", family, 37, QColor(0, 0, 255), 100, 125);
    }

    restartButton = new Button(QPixmap(":/images/bar.png"), "restart", this, 100, 125);
    restartButton->setPos(0, 125);
    //connect(restartButton, &Button::pressed, this, &popup::restart);
    text = createTextItem("Restart", family, 20, QColor(255, 255, 255), 150, 125);


    mainMenuButton = new Button(QPixmap(":/images/bar.png"), "mainmenu", this, 100, 125);
    mainMenuButton->setPos(0, 250);
   // connect(mainMenuButton, &Button::pressed, this, &popup::mainMenu);
    text = createTextItem("Main Menu", family, 20, QColor(255, 255, 255), 150, 125);


    exitButton = new Button(QPixmap(":/images/bar.png"), "Exit", this, 100, 125);
    exitButton->setPos(0, 375);
    text = createTextItem("Exit", family, 20, QColor(255, 255, 255), 150, 125);

}

void PopUp::show() {
//    exitButton->show();
//    restartButton->show();
//    resumeButton->show();
//    mainMenuButton->show();
    setVisible(true);
    clearFocus();
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

void PopUp::hide() {
//    exitButton->hide();
//    restartButton->hide();
//    resumeButton->hide();
//    mainMenuButton->hide();
    setVisible(false);
    clearFocus();
    setFlag(QGraphicsItem::ItemIsFocusable, false);
}

QGraphicsTextItem* PopUp::createTextItem(const QString& text, const QString& fontFamily, int fontSize, const QColor& color, int posX, int posY) {
    QGraphicsTextItem *item = new QGraphicsTextItem(text, this);
    QFont font;
    font.setFamily(fontFamily);
    font.setPointSize(fontSize);
    item->setFont(font);
    item->setDefaultTextColor(color);
    item->setPos(posX, posY);
    return item;
}