//
//  item.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "item.h"

item::item(char symbol):Component{symbol}{}
item::~item(){}
bool item::isDead() const {return false;}