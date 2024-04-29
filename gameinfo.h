//
// Created by marek on 26.04.2024.
//

#ifndef ICP_GAMEINFO_H
#define ICP_GAMEINFO_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include <QFontDatabase>
#include <QFont>
#include <QColor>



class GameInfo : public QGraphicsTextItem
{
Q_OBJECT
public:
    GameInfo(QGraphicsItem *parent = 0);
    ~GameInfo();
    void updateMessage(const QString& message, const QColor& color, int duration); // Add this line
private:
    QString defaultText; // Add this line
    QTimer *timer;
    int messageDuration;
public slots:
    void ouch();
    void damage();
    void resetMessage();
};


#endif //ICP_GAMEINFO_H
