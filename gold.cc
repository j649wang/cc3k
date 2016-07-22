#include "gold.h"
#include <iostream>
using namespace std;

Gold::Gold(int value, char symbol): item(symbol),value{value}{}

int Gold::getValue()const {return value;}

void Gold::notifyDragon(Cell *player){}

bool Gold::canPickUp() const {return true;}

Gold::~Gold(){}

void Gold::addDragon(Cell *curpos){}

bool Gold::isGold() const{ return true;}

void Gold::setGuard(shared_ptr<Component> guard){}

bool Gold::isDragonHoard() const {return false;}

