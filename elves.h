#ifndef _ELVES_H_
#define _ELVES_H_
#include "player.h"

class Elves: public Player{
  public:
	Elves(std::shared_ptr<Cell> cell);
	int getGold() override;
	const int maxHP()const override;
	const int maxATK()const override;
	const int maxDEF()const override;

	void drinkPotion(std::shared_ptr<Potion> p)override;

};
#endif
