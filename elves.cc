#include "elves.h"
#include "potion.h"

Elves::Elves(std::shared_ptr<Cell> cell): Player(cell,'@',140,30,10,0) {}

float Elves::getWealth(){
	return (float) wealth;
}

const int Elves::maxHP() {return 140;}
const int  Elves::maxATK(){ return 30;}
const int Elves::maxDEF() {return 10;}

void Elves::drinkPotion(Potion &p){
	int newHP = HP + ((p.getHPeffect() > 0)?p.getHPeffect(): -getHPeffect());
	int newATK = ATK + ((p.getATKeffect()>0)?p.getATKeffect(): -getATKeffect());
	int newDEF = DEF + ((p.getDEFeffect()>0)?p.getDEFeffect(): -getDEFeffect());
	if (newHP >=0 && newHP <= maxHP()) HP = newHP;
	else if (newHP < 0) HP=0;
	else HP = maxHP();
	if (newATK >=0 && newATK <= maxATK()) ATK = newATK;
	else if (newATK < 0) ATK = 0;
	else ATK = maxATK();
	if (newDEF >=0 && newDEF <= maxDEF()) DEF = newDEF;
	else if (newDEF < 0) DEF = 0;
	else DEF = maxDEF();
}
