#ifndef _WEREWOLF_H_
#define _WEREWOLF_H_
#include "enemy.h"

class Werewolf: public Enemy{
  public:
	Werewolf(std::shared_ptr<Cell> cell);
};
#endif
