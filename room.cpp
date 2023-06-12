#include "room.h"

Room::Room() {

}

Room::Room(const std::string& name, const std::string& desc, const int* dir): roomName(name), roomDesc(desc) {
    for (int i = 0; i < roomNum; i++) direction[i] = dir[i];
}

std::vector<Room> Room::setupRoom(const std::string& fileName) {
    std::ifstream newFile(fileName);
    if(!newFile) {
        std::cerr << "File operation unsuccessful." << std::flush;
        std::exit(EXIT_FAILURE);
    }
    std::vector<Room>rooms;
    std::string line;
    while (std::getline(newFile, line)) {
        std::string name, desc, gap;
        std::getline(newFile, name);
        int dir[roomNum];
        for (int i = 0; i < roomNum; i++) newFile >> dir[i];
        std::getline(newFile, gap);
        std::getline(newFile, desc);
        rooms.emplace_back(name, desc, dir);
    }
    return rooms;
}

std::string Room::getString(int a) {
    static const char* direction[roomNum] { "(L)eft", "(R)ight", "(F)ront", "(B)ack" };
    return direction[a];
}

void Room::tellRoom() {
    for (int i = 0; i < roomDesc.size(); i++) {
        std::cout << roomDesc[i];
        Sleep(60);
    } std::cout << "\n";
    Sleep(400);
    if (roomName == "EndRoom") {
        system("pause");
        system("cls");
        std::string endLine = "\nThe adventure has come to an end. Thank you for playing.\n";
        for (int i = 0; i < endLine.size(); i++) {
            std::cout << endLine[i];
            Sleep(60);
        } std::cout << "\n";
        system("pause");
        system("cls");
        exit(EXIT_SUCCESS);
    }
    std::cout << "\nYou can go: ";
    for (int i = 0; i <= roomNum; i++) {
        if (direction[i]) std::cout << getString(i) << " ";
    } std::cout << "\n";
}
