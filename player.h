#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "character.h"
#include "gold.h"
#include <memory>
#include <map>
#include <string>

class Potion;
class Enemy;

class Player: public Character{
	bool attacked;
  protected:
	int gold;
	virtual int getGold()=0;
	virtual const int maxHP()const=0;
	virtual const int maxATK()const=0;
	virtual const int maxDEF()const=0;
  public:
	std::map<std::string, int> potions;
	virtual bool haveAttacted();
	virtual void setAtkDef();
	virtual void drinkPotion(std::shared_ptr<Potion> p);
	virtual int pickGold(std::shared_ptr<Gold> g);
	virtual int attack(std::shared_ptr<Enemy> e);	
	virtual void move(std::shared_ptr<Cell> cell);
	Player(std::shared_ptr<Cell> cell,char symbol, int HP,int ATK,int DEF);
	void reset();
	~Player();
};

#endif
