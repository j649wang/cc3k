#ifndef _MHOARD_H_
#define _MHOARD_H_
#include "gold.h"

class MerchantHoard: public Gold{
  public:
	MerchantHoard(std::shared_ptr<Cell> cell);
};
	
#endif
