#include "item.h"

Item::Item(std::string& a, bool b): itemName(a), available(b) { }

std::string Item::getName() const { return itemName; }

bool Item::isAvailable() const { return available; }

void Item::setAvailability(bool a) { available = a; }