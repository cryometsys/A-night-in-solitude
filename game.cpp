#include "game.h"

void Game::newGame() {
    std::cout << "Welcome to \"ONE NIGHT IN SOLITUDE\"!\n";
    std::cout << "\n\n\nMain Menu:\n";
    std::cout << "\t1. Start Game\n";
    std::cout << "\t2. End Game\n";
    int userInput; std::cin >> userInput;
    system("cls");
    switch (userInput) {
    case 1:
        startGame();
        break;
    case 2:
        std::cout << "Exiting game...";
        Sleep(500);
        system("CLS");
        break;
    default:
        std::cout << "Invalid key. Please try again.\n";
        newGame();
    }
}

void Game::startGame() {
    Room newRoom;
    std::cout << "Please enter your name: ";
    std::string name;
    std::cin >> name;
    newPlayer.setName(name);
    system("cls");
    std::cout << "Welcome " << name << ".\n";
    std::string line = "[Some quick words before you start playing the game. This is completely a text-based game. At any time, there will be several options available to you depending on the directions you can go. Whatever direction you want to go, write the first word only. For example, if you want to go Left, just write out 'L'.\nThat is about it. Good luck on your journey.]\n\n";
    for (int i = 0; i < line.size(); i++) {
        std::cout << line[i];
        Sleep(30);
    } system("pause");
    system("cls");
    std::string fileName = "gamefile.txt";
    std::vector<std::unique_ptr<Room>> rooms = newRoom.setupRoom(fileName);
    playGame(rooms);
}

void Game::playGame(std::vector<std::unique_ptr<Room>>& rooms) {
    int r = 0;
    while(true) {
        getDesc(*rooms[r]);
        bool roomFlag = true;
        int d = -1;
        while(roomFlag) {
            int choice = showOptions();
            switch (choice) {
            case 1:
                rooms[r]->showRoom();
                std::cout << "Set direction: ";
                char userInput;
                std::cin >> userInput;
                d = getDirinString(userInput);
                if (d != -1 && rooms[r]->direction[d]) {
                    if (rooms[rooms[r]->direction[d] - 1]->needItem()) {
                        std::cout << "You need certain items to move here.\n";
                        std::cout << "Use item(s)?(Y/N): ";
                        std::cin >> userInput;
                        if (userInput == 'Y') {
                            int count = 0;
                            for (auto i : newPlayer.inventory) {
                                count += useItem(*rooms[rooms[r]->direction[d] - 1], i);
                            } if (count == 0) std::cout << "You do not have the required items.\n";
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(60));
                    break;   
                    } else {
                    r = rooms[r]->direction[d] - 1;
                    roomFlag = false;
                    system("CLS");
                    break;
                    }
                }
                std::cout << "Invalid Direction\n";
                break;
            case 2:
                newPlayer.showItem();
                std::this_thread::sleep_for(std::chrono::milliseconds(60));
                break;
            case 3: {
                bool check = rooms[r]->showItem();
                    if (check) {
                    std::cout << "Pick item(s)? (Y/N): ";
                    char playerInput; std::cin >> playerInput;
                    if (playerInput == 'Y') {
                        std::cout << "Enter item name: ";
                        std::string itemName; std::cin >> itemName;
                        getItem(*rooms[r], itemName);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(60));
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void Game::getDesc(Room& obj) { obj.tellRoom(); }

int Game::getDirinString(char a) {
    switch (a) {
    case 'L': return 0;
    case 'R': return 1;
    case 'F': return 2;
    case 'B': return 3;
    default: return -1;
    }
}

int Game::showOptions() {
    std::cout << "\nAvailable options:\n";
    std::cout << "1. Move to location\n";
    std::cout << "2. Check inventory\n";
    std::cout << "3. Check items in room\n";
    std::cout << "Your choice: ";
    int choice; std::cin >> choice;
    return choice;
}

void Game::getItem(Room& obj, std::string& item) {
    if (obj.checkItem(item)) {
        newPlayer.addItem(item);
        std::cout <<item << " has been added to inventory.\n";
        obj.removeItem(item);
    }
    else std::cout << "Invalid item.\n";
}

int Game::useItem(Room& obj, std::string& itemName) {
    if (obj.checkReq(itemName)) {
        newPlayer.removeItem(itemName);
        std::cout <<itemName << " has been used.\n";
        obj.removeReq(itemName);
        return 1;
    } return 0;
}