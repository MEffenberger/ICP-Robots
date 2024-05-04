/**
 * @file main.cpp
 * @brief Main file of the project
 * @version 1.0
 * @details Instantiates the GameMaster class and runs the game
 * @project ICP Project - Epic Robot Survival
 * @authors Marek Effenberger, Samuel Hejníček
 */

#include "gamemaster.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameMaster gameMaster;
    gameMaster.run();
    return a.exec();
}