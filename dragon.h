#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"

class DragonHoard;

class Dragon: public Enemy{
  public:
	Dragon();
    bool isDragon() const override;
};

#endif
