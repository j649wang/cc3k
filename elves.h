#ifndef _ELVES_H_
#define _ELVES_H_
#include "player.h"

class Elves: public Player{
  public:
	Elves(int row=0, int col=0,int chamber=0);
	void getWealth()const override;
	const int maxHP()const override;
	const int maxATK()const override;
	const int maxDEF()const override;

	void drinkPotion(Potion &p)override;

};
#endif
