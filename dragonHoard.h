#ifndef _DHOARD_H_
#define _DHOARD_H_
#include "gold.h"
#include "dragon.h"
#include <memory>

//override notifyDragon
class DragonHoard: public Gold{
	std::shared_ptr<Component> guard;
  public:
	DragonHoard();
    void setGuard(std::shared_ptr<Component> guard) override;
	void notifyDragon(Cell *Playernear) override;
    void addDragon(Cell *curpos) override;
    bool canPickUp() const override;
};

#endif
