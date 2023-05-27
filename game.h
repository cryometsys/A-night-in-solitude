#ifndef GAME_H
#define GAME_H

#include "room.h"

class Game {
    public:
        Game() = default;
        void newGame();
        void startGame();
        void playGame(std::vector<Room>&);
        int getDirinString(char);
        void getDesc(Room&);
};


#endif