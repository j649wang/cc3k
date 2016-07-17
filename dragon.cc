#include "dragon.h"
#include "dhoard.h"
#include <iostream>
using namespace std;

class DragonHoard;

Dragon::Dragon(shared_ptr<Cell> cell):Enemy(cell,'D',150,20,20,false,6),hostile{false}{}

void Dragon::setHostile(){
	hostile = true;
}

void Dragon::move(){return;}
