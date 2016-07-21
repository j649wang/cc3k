//
//  chamber.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/15.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "chamber.h"
#include "cell.h"
using namespace std;

Chamber::Chamber(){}

Chamber::~Chamber(){
    cells.clear();
}

vector<Cell *> Chamber::getCells(){
    return cells;
};

void Chamber::addCells(Cell * c){
    cells.emplace_back(c);
}