#include "dragon.h"
#include <iostream>
using namespace std;


Dragon::Dragon():Enemy(150, 20, 20, 'D', 0, false, false){}
bool Dragon::isDragon() const {return true;}



