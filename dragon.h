#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"

class DragonHoard;

class Dragon: public Enemy{
	bool hostile;
  public:
	Dragon(std::shared_ptr<Cell> cell);
	void move()override;
	void setHostile();
};

#endif
