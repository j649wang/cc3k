#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "enemy.h"

class Merchant: public Enemy{
	bool hostile;
  public:
	Merchant(std::shared_ptr<Cell> cell);
	bool isHostile();
};
#endif
