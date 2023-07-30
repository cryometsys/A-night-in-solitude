#include "room.h"

Room::Room() { }

Room::Room(const std::string& name, const std::string& desc, const int* dir): roomName(name), roomDesc(desc) {
    for (int i = 0; i < roomNum; i++) direction[i] = dir[i];
}

std::vector<std::unique_ptr<Room>> Room::setupRoom(const std::string& fileName) {
    std::ifstream newFile(fileName);
    if(!newFile) {
        std::cerr << "File operation unsuccessful." << std::flush;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::unique_ptr<Room>>rooms;
    std::string line;
    while (std::getline(newFile, line)) {
        std::unique_ptr<Room> newRoom = std::make_unique<Room>();
        std::string name, desc, gap, itemName, needItem;
        std::getline(newFile, newRoom->roomName);
        for (int i = 0; i < roomNum; i++) newFile >> newRoom->direction[i];
        std::getline(newFile, gap);
        std::getline(newFile, newRoom->roomDesc);
        std::getline(newFile, line);
        std::istringstream itemHasStream(line);
        while (itemHasStream >> itemName) {
            if (itemName == "none") break;
            newRoom->items.push_back(itemName);
        }
        std::getline(newFile, line);
        std::istringstream itemNeedStream(line);
        while (itemNeedStream >> needItem) {
            if (needItem == "none") break;
            newRoom->requirements.push_back(needItem);
        }
        rooms.push_back(std::move(newRoom));
    }
    return rooms;
}

std::string Room::getString(int a) {
    static const char* direction[roomNum] { "(L)eft", "(R)ight", "(F)ront", "(B)ack" };
    return direction[a];
}

void Room::tellRoom() {
    std::cout << roomName << "\n";
    std::stringstream ss(roomDesc);
    std::string buffer;
    bool printRemaining = true;
    while(std::getline(ss, buffer, '#')) {
        if (!printRemaining) {
            std::cout << "\n" << buffer << "\n";
            continue;
        }
        int i = 0;
        for (; i < buffer.size(); i++) {
            std::cout << buffer[i];
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
            if (keyPressed()) {
                printRemaining = false;
                break;
            }
            if (i == buffer.size() - 1) printRemaining = true;
        }
        if (!printRemaining && i < buffer.size()) std::cout << buffer.substr(i + 1);
    }
    std::cout << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    if (roomName == "EndRoom") {
        system("pause");
        system("cls");
        std::string endLine = "\nThe adventure has come to an end. Thank you for playing.\n";
        for (int i = 0; i < endLine.size(); i++) {
            std::cout << endLine[i];
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        } std::cout << "\n";
        system("pause");
        system("cls");
        exit(EXIT_SUCCESS);
    }
}

bool keyPressed() {
    #ifdef _WIN32
        return (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    #else
        struct termios oldSettings, newSettings;
        tcgetattr(fileno(stdin), &oldSettings);
        newSettings = oldSettings;
        newSettings.c_lflag &= (~ICANON & ~ECHO);
        tcsetattr(fileno(stdin), TCSANOW, &newSettings);
        int key = getchar();
        tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
        return key == ' ';
    #endif
}

void Room::showRoom() {
    std::cout << "\nYou can go: ";
    for (int i = 0; i <= roomNum; i++) {
        if (direction[i]) std::cout << getString(i) << " ";
    } std::cout << "\n";
}

bool Room::showItem() {
    if (items.empty()) {
        std::cout << "There are no items to look for.\n";
        return false;
    }
    else {
        std::cout << "\nYou look around the room. You find: ";
        for (int i = 0; i < items.size(); i++) {
            std::cout << items[i] << " ";
        } std::cout << "\n\n";
        return true;
    }
}

bool Room::needItem() {
    if (requirements.empty()) return false;
    return true;
}

std::vector<std::string>& Room::getItem() { return requirements; }

bool Room::checkReq(const std::string& itemName) {
    for (int i = 0; i < requirements.size(); i++) {
        if (requirements[i] == itemName) return true;
    } return false;
}

bool Room::checkItem(const std::string& itemName) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i] == itemName) return true;
    } return false;
}

void Room::removeItem(std::string item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Room::removeReq(std::string item) {
    requirements.erase(std::remove(requirements.begin(), requirements.end(), item), requirements.end());
}