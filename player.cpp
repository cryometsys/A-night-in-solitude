#include "player.h"

Player::Player(std::string a): playerName(a) {}

Player::Player(Player& obj) {
    playerName = obj.playerName;
    inventory = obj.inventory;
}

void Player::getItem(std::string item) { inventory.push_back(item); }

void Player::removeItem(std::string item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}