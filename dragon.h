#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"

class DragonHoard;

class Dragon: public Enemy{
  public:
	Dragon(std::shared_ptr<Cell> cell);
	void notify(DragonHoard &dh);
	void move()override;
};

#endif
