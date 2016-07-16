#ifndef _ELVES_H_
#define _ELVES_H_
#include "player.h"

class Elves: public Player{
  public:
	Elves(std::shared_ptr<Cell> cell);
	void getWealth()const override;
	const int maxHP()const override;
	const int maxATK()const override;
	const int maxDEF()const override;

	void drinkPotion(Potion &p)override;

};
#endif
