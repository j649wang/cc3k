#include "component.h"
#include "cell.h"
using namespace std;

int Component::getRow() const{
    return row;
}
int Component::getCol() const{
    return col;
}
char Component::getSymbol() const{
    return symbol;
}

void Component::setRow(int i){
    row = i;
}
void Component::setCol(int j){
    col = j;
}
void Component::setCoords(const Cell &c){
    setRow(c.getRow());
    setCol(c.getCol());
}
bool Component::isEnemy() const { return false;}

bool Component::isGold() const { return false;}

bool Component::isPotion() const { return false;}

bool Component::isPlayer() const {return false;}

bool Component::isDragon() const {return false;}

bool Component::isMerchant() const{ return false;}

void Component::setHostile(bool hostile){};

Component::Component(char symbol):symbol{symbol}{}

Component::~Component(){}