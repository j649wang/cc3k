#include "character.h"
#include <math.h>
using namespace std;

Character::Character(shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF): Component(cell,symbol),HP{HP},ATK{ATK},DEF{DEF} {}

int Character::getATK()const {return ATK;}
int Character::getDEF()const {return DEF;}
int Character::getHP()const {return HP;}

bool Character::isDead(){
	if(HP) return false;
	else return true;
}

void Character::attack(Character &c){
	if (isDead()) return;
	int damage;
	damage = ceil(100.0/(100+c.getDEF()))* ATK;
	HP = HP - damage;
}

Character::~Character() {}
