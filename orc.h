//
//  orc.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef orc_hpp
#define orc_hpp

#include "player.h"
//override getGold;
class Orc: public Player{
public:
    Orc();
    double getGold() const override;
};
#endif /* orc_hpp */
