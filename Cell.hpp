//
//  Cell.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <vector>
#include <iostream>

class Gold;
class Display;
class Enemy;
class Component;
class Chamber;
class Player;
class Cell{
    int row;
    int col;
    std::shared_ptr<Chamber> chamber;
    std::vector<std::shared_ptr<Cell>> neighbors;
    std::shared_ptr<Display> theDisplay;
    std::shared_ptr<Component>component;
    char symbol;
public:
    Cell(int row, int col, std::shared_ptr<Display>display, char symbol);
    void notifydisplay();
    bool canPcWalk();
    bool canEnemyWalk();
    void attach(const std::shared_ptr<Cell> c);
    
    std::shared_ptr<Cell> findPlayer();
    std::shared_ptr<Cell> findwalkable();
    
    //getters
    std::shared_ptr<Chamber> getChamber();
    void setChamber(std::shared_ptr<Chamber> chamber);
    int getRow();
    int getCol();
    char getSymbol();
    std::shared_ptr<Component> getComponent();
    //mutators
    void setComponent(const std::shared_ptr<Component> c);
};

#endif /* Cell_hpp */
