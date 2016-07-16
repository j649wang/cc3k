#ifndef _DHOARD_H_
#define _DHOARD_H_
#include "gold.h"
#include "dragon.h"
#include <memory>


class DragonHoard: public Gold{
	std::unique_ptr<Dragon> guard;
  public:
	DragonHoard(std::shared_ptr<Cell> cell, std::unique_ptr<Dragon> guard);
};

#endif
