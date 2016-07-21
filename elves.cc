#include "elves.h"
#include "potion.h"
#include "cell.h"
#include <cmath>

using namespace std;

Elves::Elves(): Player(140, 30, 10, "Elves") {}

void Elves::drinkPotion(shared_ptr<Potion> p, Cell *targetcell){
    setHP(getHP() + abs(p->getHPeffect()));
    setATK(getATK() + abs(p->getATKeffect()));
    setDEF(getDEF() + abs(p->getDEFeffect()));
    targetcell->componentLeft();
}
