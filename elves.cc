#include "elves.h"
#include "potion.h"

Elves::Elves(std::shared_ptr<Cell> cell): Player(cell,'@',140,30,10) {}

int Elves::getGold(){
	return gold/2;
}

const int Elves::maxHP()const {return 140;}
const int  Elves::maxATK()const{ return 30;}
const int Elves::maxDEF()const  {return 10;}

void Elves::drinkPotion(std::shared_ptr<Potion> p){
	int newHP = HP + ((p->getHPeffect() > 0)?p->getHPeffect(): -p->getHPeffect());
	int newATK = ATK + ((p->getATKeffect()>0)?p->getATKeffect(): -p->getATKeffect());
	int newDEF = DEF + ((p->getDEFeffect()>0)?p->getDEFeffect(): -p->getDEFeffect());
	if (newHP >=0 && newHP <= maxHP()) HP = newHP;
	else if (newHP < 0) HP=0;
	else HP = maxHP();
	if (newATK >=0) ATK = newATK;
	else if (newATK < 0) ATK = 0;
	else ATK = maxATK();
	if (newDEF >=0) DEF = newDEF;
	else if (newDEF < 0) DEF = 0;
	else DEF = maxDEF();
	++potions[p->getType()];
}
