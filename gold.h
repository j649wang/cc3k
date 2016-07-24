#ifndef _GOLD_H_
#define _GOLD_H_
#include "item.h"
#include <string>

class Character;

class Gold: public item{
	int value;
  public:
    virtual int getValue() const;
    
    virtual void notifyDragon(Cell *Playernear);
    
    virtual bool canPickUp() const;
    
    virtual void setGuard(std::shared_ptr<Character> guard);
    
    Gold(int value, char symbol = 'G');
    
    bool isGold() const override;
    
    void setValue(int i);
    
    virtual ~Gold() = 0;   
    
    virtual bool isDragonHoard() const;
};
#endif
