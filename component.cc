#include "component.h"
#include "cell.h"

using namespace std;

Component::Component(shared_ptr<Cell> cell, char symbol): cell{cell},symbol{symbol} {}

shared_ptr<Cell> Component::getCell() {return cell;}

char Component::getSymbol()const {return symbol;}
void Component::setCell(shared_ptr<Cell> cp){cell = cp;}

Component::~Component(){}
