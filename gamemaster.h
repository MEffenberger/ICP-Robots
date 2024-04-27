//
// Created by marek on 27.04.2024.
//

#ifndef ICP_GAMEMASTER_H
#define ICP_GAMEMASTER_H

#include <QObject>
#include <map>
#include <vector>
#include <string>


class GameMaster : public QObject {


private:
    std::vector<std::vector<int>> Enemy;
    std::vector<int> User;
    std::pair<int, int> Obstacle;
    int timeLimit;


};


#endif //ICP_GAMEMASTER_H
