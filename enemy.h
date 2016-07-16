#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "character.h"

class Enemy: public Character{
	bool moveable;
  public:
	Enemy(std::shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF, bool moveable);
	virtual void move();
	~Enemy();
};
#endif
