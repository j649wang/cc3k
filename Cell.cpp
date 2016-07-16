

//
//  Cell.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "Cell.hpp"
#include "Display.hpp"
class Gold{
public:
    bool canPickup();
};

using namespace std;
Cell::Cell(int row, int col, std::shared_ptr<Display> display, char symbol):row{row}, col{col}, theDisplay{display}, component{nullptr}, chamber{-1}, symbol{symbol}{}

void Cell::notifydisplay(){
    theDisplay->notify(*this);
}

bool Cell::canPcWalk(){;
    if(shared_ptr<Gold> dr = dynamic_pointer_cast<Gold>(component)){
        return !dr->canPickup();
    }else {
        return (((symbol == '.')||(symbol == '+')||(symbol=='#'))&&(!component)); //walkable tile and not occupied;
    }
}

bool Cell::canEnemyWalk(){
    return ((symbol == '.')&&(!component));
}

void Cell::attach(const shared_ptr<Cell> c){
    neighbors.emplace_back(c);
}

shared_ptr<Cell> Cell::findPlayer(){
    for(int i = 0; i < neighbors.size(); ++i){
        if(dynamic_pointer_cast<Player>(neighbors[i]->getComponent())){
            return neighbors[i];
        }
    }
    return nullptr;
}

shared_ptr<Cell> Cell::findwalkable(){
    vector<shared_ptr<Cell>> walkableset;
    for(int i = 0; i < neighbors.size(); ++i){
        if(neighbors[i]->canEnemyWalk()){
            walkableset.push_back(neighbors[i]);
        }
    }
    if(walkableset.size()== 0){
        return nullptr;
    }else {
        int r = rand()% walkableset.size();
        return walkableset[r];
    }
}

std::shared_ptr<Chamber> Cell::getChamber(){
    return chamber;
}

void Cell::setChamber(std::shared_ptr<Chamber> i){
    chamber = i;
}

char Cell::getSymbol(){
    if(component){
        return component->getSymbol();
    }else {
        return symbol;
    }
}
std::shared_ptr<Component> Cell::getComponent(){
    return component;
}
void Cell::setComponent(const std::shared_ptr<Component> c){
    component = c;
    notifydisplay();
}

int Cell::getRow(){
    return row;
}

int Cell::getCol(){
    return col;
}
