//
//  chamber.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/15.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "Chamber.hpp"
#include "Cell.hpp"
using namespace std;
Chamber::Chamber(){}

Chamber::~Chamber(){
    cells.clear();
}

void Chamber::addCells(shared_ptr<Cell> c){
    cells.push_back(c);
}