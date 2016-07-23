
#include "dwarf.h"

Dwarf::Dwarf(): Player(100, 20, 30, "Dwarf") {}

double Dwarf::getGold() const{
    double gold = Player::getGold();
    return 2 * gold;
}

//override getGold;
