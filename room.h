#ifndef ROOM_H
#define ROOM_H

#include "item.h"

enum { left, right, front, back, roomNum };

class Room {
    public:
        Room();
        Room(const std::string&, const std::string&, const int* dir);
        std::string getString(int);
        std::vector<Room> setupRoom(const std::string&);
        void tellRoom();
        int direction[roomNum];
        std::vector<Item>& getItems();
    private:
        std::string roomName;
        std::string roomDesc;
        std::vector<Item> items;
        Player newPlayer;
};

#endif