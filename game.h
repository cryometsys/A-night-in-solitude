#ifndef GAME_H
#define GAME_H

#include "room.h"

class Game {
    Player newPlayer;
public:
    Game() = default;
    void newGame();
    void startGame();
    void playGame(std::vector<std::unique_ptr<Room>>&);
    int getDirinString(char);
    void getDesc(Room&);
    int showOptions();
    void getItem(Room&, std::string&);
    int useItem(Room&, std::string&);
};

#endif