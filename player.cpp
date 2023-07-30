#include "player.h"

Player::Player(std::string a): playerName(a) {}

Player::Player(Player& obj) {
    playerName = obj.playerName;
    inventory = obj.inventory;
}

void Player::setName(std::string& name) { playerName = name; }

void Player::addItem(std::string item) { inventory.push_back(item); }

void Player::removeItem(std::string item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

void Player::showItem() {
    if (inventory.empty()) { std::cout << "There are no items in your inventory.\n"; return; }
    for (int i = 0; i < inventory.size(); i++) 
        std::cout << inventory[i] << " ";
    std::cout << "\n";
}