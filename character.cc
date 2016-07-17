#include "character.h"
#include <math.h>
#include <memory>

using namespace std;

Character::Character(shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF): Component(cell,symbol),HP{HP},ATK{ATK},DEF{DEF} {}

int Character::getATK()const {return ATK;}
int Character::getDEF()const {return DEF;}
int Character::getHP()const {return HP;}


bool Character::isDead(){
	if(HP) return false;
	else return true;
}

int Character::setHP(const int n) {HP = n;}


Character::~Character() {}
