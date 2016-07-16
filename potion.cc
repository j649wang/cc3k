#include "potion.h"
#include "player.h"

using namespace std;

class player;

Potion::Potion(shared_ptr<Cell> cell, char symbol, string type,int HPeffect,int ATKeffect,int DEFeffect):Component(cell,symbol), type{type},HPeffect{HPeffect},ATKeffect{ATKeffect},DEFeffect{DEFeffect} {}

void Potion::beDrunk(Player &p){
	p.drinkPotion(*this);
}

string Potion::getType()const {return type;}

int Potion::getHPeffect()const {return HPeffect;}

int Potion::getATKeffect()const {return ATKeffect;}

int Potion::getDEFeffect()const {return DEFeffect;}

Potion::~Potion() {}
