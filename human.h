#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "player.h"

//override getScore
class Human: public Player{
  public:
    Human();
    int getScore() override;
};

#endif
