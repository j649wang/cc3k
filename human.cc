#include "human.h"

Human::Human(): Player(140, 20, 20, "Human") {}

double Human::getScore(){return 1.5 * getGold();}
