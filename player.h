#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "character.h"
#include "gold.h"


class Potion;

class Player: public Character{
	int wealth;
  protected:
	virtual float getWealth()=0;
	virtual const int maxHP()const=0;
	virtual const int maxATK()const=0;
	virtual const int maxDEF()const=0;
  public:
	virtual void setAtkDef();
	virtual void drinkPotion(Potion &p);
	virtual void pickGold(Gold &g);
	
	virtual void move(std::shared_ptr<Cell> cell);
	Player(std::shared_ptr<Cell> cell,char symbol, int HP,int ATK,int DEF, int wealth);
	~Player();
};

#endif
