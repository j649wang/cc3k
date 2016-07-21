//
//  dwarf.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef dwarf_hpp
#define dwarf_hpp

#include "player.h"
//override getGold;
class Dwarf: public Player{
public:
    Dwarf();
    double getGold() const override;
};
#endif /* dwarf_hpp */
