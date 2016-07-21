#ifndef _ELVES_H_
#define _ELVES_H_
#include "player.h"

//override drinkPotion
class Elves: public Player{
  public:
	Elves();
	void drinkPotion(std::shared_ptr<Potion> p, Cell *targetcell) override;
};
#endif
