/**
 * @file gameinfo.h
 * @brief GameInfo class header file
 * @version 1.0
 * @details This class is responsible for creating a little text box in the game
 * @project ICP Project - Epic Robot Survival
 * @author Marek Effenberger
 */

#ifndef ICP_GAMEINFO_H
#define ICP_GAMEINFO_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include <QFontDatabase>
#include <QFont>
#include <QColor>

/**
 * @brief GameInfo class, inherits from QObject and QGraphicsTextItem
 */
class GameInfo : public QGraphicsTextItem
{
Q_OBJECT
public:

    /**
     * @brief GameInfo constructor
     * @param parent Parent QGraphicsItem
     */
    GameInfo(QGraphicsItem *parent = 0);

    /**
     * @brief GameInfo destructor
     */
    ~GameInfo();

    /**
     * @brief Update the message in the text box
     * @param message Message to be displayed
     * @param color Color of the message
     * @param duration Duration of the message
     */
    void updateMessage(const QString& message, const QColor& color, int duration);

private:

    /** Default text */
    QString defaultText;

    /** Timer for the message duration */
    QTimer *timer;

    /** Duration of the message - used while being paused */
    int messageDuration;

public slots:

    /**
     * @brief Display the "OUCH!" message
     */
    void ouch();

    /**
     * @brief Display the "SH*T!" message
     */
    void damage();

    /**
     * @brief Reset the message to the default text
     */
    void resetMessage();
};


#endif //ICP_GAMEINFO_H
