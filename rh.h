#ifndef _RH_H_
#define _RH_H_
#include "potion"

class RH: public Potion{
  public:
	RH(std::shared_ptr<Cell> cell);
};
#endif
