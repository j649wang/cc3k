//
//  orc.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "orc.h"
//override getGold;

Orc::Orc(): Player(180, 30, 25, "Orc"){}

double Orc::getGold() const{return 0.5*getGold();}
