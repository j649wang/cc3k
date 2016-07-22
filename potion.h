#ifndef _POTION_H_
#define _POTION_H_
#include "component.h"
#include "item.h"
#include <string>
#include <memory>

class Player;

class Potion: public item{
	std::string name;
    std::string description;
	int HPeffect;
	int ATKeffect;
	int DEFeffect;
  public:
	std::string getName() const;
    std::string describe() const;
	int getHPeffect() const;
	int getATKeffect() const;
	int getDEFeffect() const;
    bool isPotion() const override;
    Potion(std::string name, int HPeffect,int ATKeffect,int DEFeffect,char symbol = 'P');
	virtual ~Potion() = 0;
};

#endif
