#ifndef _POTION_H_
#define _POTION_H_
#include "component.h"
#include <string>
#include <memory>

class Player;

class Potion: public Component, public std::enable_shared_from_this<Potion>{
	std::string type;
	int HPeffect;
	int ATKeffect;
	int DEFeffect;
  public:
	std::string getType()const;
	int getHPeffect()const;
	int getATKeffect()const;
	int getDEFeffect()const;
	Potion(std::shared_ptr<Cell> cell,char symbol,std::string type,int HPeffect,int ATKeffect,int DEFeffect);
	virtual void beDrunk(std::shared_ptr<Player> p);
	~Potion();
};

#endif
