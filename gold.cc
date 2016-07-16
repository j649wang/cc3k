#include "gold.h"

using namespace std;

Gold::Gold(shared_ptr<Cell> cell, char symbol, int value, string type): Component(cell,symbol),value{value},type{type} {}

int Gold::getValue()const {return value;}
string Gold::getType()const {return type;}

Gold::~Gold() {}
