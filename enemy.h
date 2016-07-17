#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "character.h"

class Player;

class Enemy: public Character{
	bool moveable;
	int gold;
	bool hasmoved;
  public:
	Enemy(std::shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF, bool moveable, int gold);
	virtual bool moved();
	virtual int attack(std::shared_ptr<Player> p);
	virtual int getGold()const;
	virtual void move();
	void reset();
	~Enemy();
};
#endif
