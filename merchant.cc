#include "merchant.h"

static bool Merchant::hostile = false;

Merchant::Merchant(std::shared_ptr<Cell> cell):Enemy(cell,'M',30,70,5,true,4) {}

bool Merchant::isHostile() {
	if (getHP() < 30) {
		hostile = true;
	}
	return hostile;
}
