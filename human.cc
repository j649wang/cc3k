#include "human.h"

Human::Human(std::shared_ptr<Cell> cell): Player(cell,'@',140,20,20) {}

int Human::getGold(){
	return gold; 
}

const int Human::maxHP() const{return 140;}
const int Human::maxATK()const {return 20;}
const int Human::maxDEF()const {return 20;}

