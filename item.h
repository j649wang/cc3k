//
//  item.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef item_hpp
#define item_hpp
#include "component.h"

class item: public Component{
public:
    item(char symbol);
    bool isDead()  const override;
    virtual ~item() = 0;
};

#endif /* item_hpp */
