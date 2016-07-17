#include "dhoard.h"
using namespace std;

DragonHoard::DragonHoard(shared_ptr<Cell> cell, unique_ptr<Dragon> guard): Gold(cell,'G', 6, "Dragon Hoard"),guard{move(guard)} {}

void Dragon::notifyDragon(){
	if (getCell()->findPlayer() &&
		 guard->getCell()->findPlayer()) {
		guard->attack();
}
