#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>
#include <memory>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

struct Player {
    std::string playerName;
    std::vector<std::string> inventory;
    Player() = default;
    Player(std::string);
    Player(Player&);
    void setName(std::string&);
    void addItem(std::string);
    void removeItem(std::string);
    void showItem();
};

#endif