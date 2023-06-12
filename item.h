#ifndef ITEM_H
#define ITEM_H

#include "player.h"

class Item {
    std::string itemName;
    bool available;
public:
    Item() = default;
    Item(std::string&, bool);
    std::string getName() const;
    bool isAvailable() const;
    void setAvailability(bool);
};

#endif