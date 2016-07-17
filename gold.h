#ifndef _GOLD_H_
#define _GOLD_H_
#include "component.h"
#include <string>

class Gold: public Component{
	int value;
	std::string type;
  protected:
	virtual void notifyDragon()=0;
  public:
	virtual int getValue()const;
	virtual std::string getType()const;	
	Gold(std::shared_ptr<Cell> cell, char symbol, int value, std::string type);
	~Gold();
};
#endif
