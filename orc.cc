//

#include "orc.h"
//override getGold;

Orc::Orc(): Player(180, 30, 25, "Orc"){}

double Orc::getGold() const{
    double gold = Player::getGold();
    return 0.5*gold;
}

