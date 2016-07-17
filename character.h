#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "component.h"
#include <memory>

class Character: public Component{
  protected:
	int HP;
	int ATK;
	int DEF;

  public:
	virtual int setHP(const int n);	
	Character(std::shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF);
	virtual int  getATK()const;
	virtual int  getDEF()const;
	virtual int  getHP()const;
	virtual bool isDead();
	~Character();
};
#endif
