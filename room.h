#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>

enum { left, right, front, back, roomNum };

class Room {
    public:
        Room();
        Room(const std::string&, const std::string&, const int* dir);
        std::string getString(int);
        std::vector<Room> setupRoom(const std::string&);
        void tellRoom();
        int direction[roomNum];
    private:
        std::string roomName;
        std::string roomDesc;
};

#endif