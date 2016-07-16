#include "merchant.h"

Merchant::Merchant(std::shared_ptr<Cell> cell):Enemy(cell,'M',30,70,5,false) {}

bool Merchant::isHostile() {
	if (getHP() < 30) {
		hostile = true;
	}
	return hostile;
}
