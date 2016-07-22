#ifndef _GOLD_H_
#define _GOLD_H_
#include "item.h"
#include <string>

class Dragon;

class Gold: public item{
	int value;
  public:
	virtual int getValue() const;
    
    virtual void notifyDragon(Cell *Playernear);
    
    virtual bool canPickUp() const;
    
    virtual void setGuard(std::shared_ptr<Component> guard);
    
	Gold(int value, char symbol = 'G');
    
    bool isGold() const override;
    
    virtual ~Gold() = 0;
    
    virtual void addDragon(Cell *curpos);
    
    virtual bool isDragonHoard() const;
};
#endif
