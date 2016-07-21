

//
//  Cell.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "cell.h"
#include "display.h"
#include "player.h"
#include "potion.h"
#include "gold.h"

using namespace std;

Cell::Cell(int row, int col, std::shared_ptr<Display> display, char symbol):row{row}, col{col}, theDisplay{display}, displayComponent{nullptr}, overlapComponent{nullptr},chamber{-1}, symbol{symbol}{}

void Cell::notifydisplay(){
    theDisplay->notify(*this);
}
void Cell::setDisplayComponent(const std::shared_ptr<Component> c){
    displayComponent = c;
    notifydisplay();
}
void Cell::setOverlapComponent(const std::shared_ptr<Component> c){ overlapComponent = c;}

int Cell::getRow() const{ return row;}

int Cell::getCol() const{ return col;}

void Cell::setSymbol(char s){
    symbol = s;
    notifydisplay();
}

vector<Cell *> Cell::getneighbors() const{ return neighbors;}

bool Cell::canPcWalk() const{;
    if(dynamic_pointer_cast<Gold>(displayComponent)){
        //walk on gold
        return true;
    }else{
        return (((symbol == '.')||(symbol == '+')||(symbol=='#'))&&(!displayComponent));
        //walkable tile and not occupied;
    }
}

bool Cell::canEnemyWalk() const{
    return ((symbol == '.')&&(!displayComponent));
}

void Cell::attach(Cell *c){
    neighbors.emplace_back(c);
}

char Cell::getTileSymbol() const{ return symbol;};

shared_ptr<Component> Cell::findDragon(){
    for(auto c: neighbors){
        if(c && (c->getDisplayComponent()->isPotion())){
            return c->getDisplayComponent();
        }
    }
    return nullptr;
}

vector<shared_ptr<Potion>> Cell::findPotions(){
    vector<shared_ptr<Potion>> potionList;
    for(auto c: neighbors){
        if(c){
            shared_ptr<Component> nc = c->getDisplayComponent();
            if(nc->isPotion()){
                shared_ptr<Potion> p = dynamic_pointer_cast<Potion>(nc);
                potionList.emplace_back(p);
            }
        }
    }
    return potionList;
}

Cell *Cell::findPlayer() const{
    for(auto c: neighbors){
        if((c)&&(c->getDisplayComponent()->isPlayer())){
            return c;
        }
    }
    return nullptr;
}

Cell *Cell::findWalkable() const{
    vector<Cell *> walkableset;
    for(auto c: neighbors){
        if(c &&(c ->canEnemyWalk())){
            walkableset.emplace_back(c);
        }
    }
    if(walkableset.size()== 0){
        return nullptr;
    }else {
        int r = rand()% walkableset.size();
        return walkableset[r];
    }
}

void Cell::componentLeft(){
    displayComponent = nullptr;
    if(overlapComponent){
        displayComponent = overlapComponent;
        overlapComponent = nullptr;
    }
    notifydisplay();
}

int Cell::getChamber() const{ return chamber;}

void Cell::setChamber(int i){ chamber = i;}


char Cell::getSymbol() const{
    if(displayComponent){
        return displayComponent->getSymbol();
    }else {
        return symbol;
    }
}

std::shared_ptr<Component> Cell::getDisplayComponent() const{ return displayComponent;}

std::shared_ptr<Component> Cell::getOverlapComponent() const{ return overlapComponent;}
