#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <memory>
#include "cell.h"

class Component{
	std::shared_ptr<Cell> cell; 
	char symbol;
  public:
	virtual std::shared_ptr<Cell>  getCell();
	virtual char getSymbol() const;
	virtual void setCell(std::shared_ptr<Cell> cp);

	Component(std::shared_ptr<Cell> cell, char symbol);
	~Component();
};
#endif
