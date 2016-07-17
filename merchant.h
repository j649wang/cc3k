#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "enemy.h"

class Merchant: public Enemy{
	static bool hostile;
  public:
	Merchant(std::shared_ptr<Cell> cell);
	bool isHostile();
};
#endif
