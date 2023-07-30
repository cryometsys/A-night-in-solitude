#ifndef ROOM_H
#define ROOM_H

#include "player.h"

enum { left, right, front, back, roomNum };

class Room {
    public:
        Room();
        Room(const std::string&, const std::string&, const int* dir);
        // Room(Room&);
        std::string getString(int);
        std::vector<std::unique_ptr<Room>> setupRoom(const std::string&); //Setups the rooms
        void tellRoom(); //Gives room description
        void showRoom(); //Shows available rooms depending on availability
        bool showItem(); //Shows available items in the room
        bool needItem(); //Shows required items for the room
        std::vector<std::string>& getItem(); //Returns the requirements string
        bool checkReq(const std::string&); //Checks whether the given item is required or not
        bool checkItem(const std::string&); //Checks whether the item exists in the room
        void removeItem(std::string); //Removes the item from the room
        void removeReq(std::string); //Removes requirement from the room
        int direction[roomNum];
    private:
        std::string roomName;
        std::string roomDesc;
        std::vector<std::string> items;
        std::vector<std::string> requirements;
};

bool keyPressed();

#endif