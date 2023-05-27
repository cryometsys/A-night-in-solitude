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
    std::string line = "[Some quick words before you start playing the game. This is completely a text-based game. At any time, there will be several options available to you depending on the directions you can go. Whatever direction you want to go, write the first word only. For example, if you want to go Left, just write out 'L'.\nThat is about it. Good luck on your journey.]\n\n";
    for (int i = 0; i < line.size(); i++) {
        std::cout << line[i];
        Sleep(30);
    } system("pause");
    system("cls");
    std::string fileName = "gamefile.txt";
    std::vector<Room> rooms = newRoom.setupRoom(fileName);
    playGame(rooms);
}

void Game::getDesc(Room& obj) {
    obj.tellRoom();
}

void Game::playGame(std::vector<Room>& rooms) {
    int r = 0;
    while(true) {
        getDesc(rooms[r]);
        int d = -1;
        while(true) {
            std::cout << "Your choice: ";
            char userInput;
            std::cin >> userInput;
            d = getDirinString(userInput);
            if (d != -1 && rooms[r].direction[d]) break;
            std::cout << "Invalid Direction\n";
        }
        r = rooms[r].direction[d] - 1;
        system("CLS");  
    }
}

int Game::getDirinString(char a) {
    switch (a) {
    case 'L': return 0;
    case 'R': return 1;
    case 'F': return 2;
    case 'B': return 3;
    default: return -1;
    }
}