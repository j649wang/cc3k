//
//  dwarf.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "dwarf.h"

Dwarf::Dwarf(): Player(100, 20, 30, "Dwarf") {}

double Dwarf::getGold() const{return 2*getGold();}

//override getGold;