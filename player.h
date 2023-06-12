#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Player {
    std::string playerName;
    std::vector<std::string> inventory;
public:
    Player() = default;
    Player(std::string);
    Player(Player&);
    void getItem(std::string);
    void removeItem(std::string);
};

#endif