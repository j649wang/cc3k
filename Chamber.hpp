//
//  chamber.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/15.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef chamber_hpp
#define chamber_hpp

#include <stdio.h>
#include <memory>
#include <vector>

class Cell;

class Chamber{
    std::vector<std::shared_ptr<Cell>> cells;
public:
    Chamber();
    ~Chamber();
    void addCells(std::shared_ptr<Cell> c);
};
#endif /* chamber_hpp */
