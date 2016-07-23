//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <string>

class Display;
class Component;
class Potion;

class Cell{
    int row;
    int col;
    int chamber;
    std::map<std::string, Cell*> neighbours;
    std::shared_ptr<Display> theDisplay;
    std::shared_ptr<Component> displayComponent;
    std::shared_ptr<Component> overlapComponent;
    char symbol;
public:
    Cell(int row, int col, std::shared_ptr<Display>display, char symbol); //*
    void notifydisplay();  //*
    bool canPcWalk() const;
    bool canEnemyWalk() const;
    void attach(Cell *c, std::string dir); ///
    void componentLeft();  //
    Cell *findPlayer() const;
    Cell *findWalkable() const;
    std::vector<std::shared_ptr<Potion>> findPotions(); //*
    std::shared_ptr<Component> findDragon();
    
    //getters
    int getChamber() const; //*
    char getTileSymbol() const;
    char getSymbol() const; 
    std::map<std::string, Cell*> getneighbors() const;
    int getRow() const; //*
    int getCol() const; //
    std::shared_ptr<Component> getDisplayComponent() const;
    std::shared_ptr<Component> getOverlapComponent() const;
    //mutators
    void setDisplayComponent(const std::shared_ptr<Component> c);
    void setOverlapComponent(const std::shared_ptr<Component> c);
    void setChamber(int chamber);
    void setSymbol(char s);
};

#endif /* Cell_hpp */
