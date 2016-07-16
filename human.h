#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "player.h"

class Human: public Player{
  public:
	Human(std::shared_ptr<Cell> cell);
	float getWealth()const override;
	const int maxHP()const override;
	const int maxATK()const override;
	const int maxDEF()const override;
};

#endif
