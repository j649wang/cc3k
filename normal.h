#ifndef _NORMAL_H_
#define _NORMAL_H_
#include "gold.h"

class Normal: public Gold{
  public:
	Normal(std::shared_ptr<Cell> cell);
};

#endif
