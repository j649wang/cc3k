#include "dragon.h"
#include "dhoard.h"
#include <iostream>
using namespace std;

class DragonHoard;

Dragon::Dragon(shared_ptr<Cell> cell):Enemy(cell,'D',150,20,20,false){}

void Dragon::notify(DragonHoard &dh){
	cout << "Notifed by " << dh.getType() << endl;
}

void Dragon::move(){return;}
