#ifndef _DHOARD_H_
#define _DHOARD_H_
#include "gold.h"
#include "dragon.h"
#include <memory>

//override notifyDragon
class DragonHoard: public Gold{
    std::shared_ptr<Character> guard;
  public:
    DragonHoard();
    void setGuard(std::shared_ptr<Character> guard) override;
    void notifyDragon(Cell *Playernear) override;
    bool canPickUp() const override;
    bool isDragonHoard() const override;
};

#endif
