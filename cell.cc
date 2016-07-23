#include "cell.h"
#include "display.h"
#include "player.h"
#include "potion.h"
#include "gold.h"

using namespace std;

Cell::Cell(int row, int col, std::shared_ptr<Display> display, char symbol):row{row}, col{col},chamber{-1}, theDisplay{display}, displayComponent{nullptr}, overlapComponent{nullptr}, symbol{symbol}{}

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

int Cell::getChamber() const{ return chamber;}

void Cell::setChamber(int i){ chamber = i;}


char Cell::getSymbol() const{
    if(displayComponent){
        return displayComponent->getSymbol();
    }else {
        return symbol;
    }
}
std::map<std::string, Cell*>  Cell::getneighbors() const{ return neighbours;}

bool Cell::canPcWalk() const{;
    if(displayComponent){
        if(displayComponent->isGold()){
            //walk on gold
            return true;
        }
    }
    return (((symbol == '.')||(symbol == '+')||
             (symbol=='#')||(symbol == '\\'))&&(!displayComponent));
        //walkable tile and not occupied;
}

bool Cell::canEnemyWalk() const{
    return ((symbol == '.')&&(!displayComponent));
}

void Cell::attach(Cell *c, string dir){
    neighbours[dir] = c;
}

char Cell::getTileSymbol() const{ return symbol;};

shared_ptr<Component> Cell::findDragon(){
    for(auto c: neighbours){
        if(c.second){
           shared_ptr<Component> nc = c.second->getDisplayComponent();
            if(nc){
                if(nc->isDragon()){
                    return c.second->getDisplayComponent();
                }
            
            }
        }
    }
    return nullptr;
}

vector<shared_ptr<Potion>> Cell::findPotions(){
    vector<shared_ptr<Potion>> potionList;
    for(auto c: neighbours){
        if(c.second){
            shared_ptr<Component> nc = c.second->getDisplayComponent();
            if(nc){
                if(nc->isPotion()){
                    shared_ptr<Potion> p = dynamic_pointer_cast<Potion>(nc);
                    potionList.emplace_back(p);
                }
            }
        }
    }
    return potionList;
}

Cell *Cell::findPlayer() const{
    for(auto c: neighbours){
        if(c.second){
            if(shared_ptr<Component> dc = c.second->getDisplayComponent()){
                if(dc->isPlayer()) return c.second;
                
            }
        }
    }
    return nullptr;
}

Cell *Cell::findWalkable() const{
    vector<Cell *>walkableset;
    for(auto c: neighbours){
        if(c.second){
            if(c.second->canEnemyWalk()){
                walkableset.emplace_back(c.second);
            }
        }
    }
    if(walkableset.size()== 0){
        return nullptr;
    }else {
        int r = rand() % walkableset.size();
        return walkableset[r];
    }
}

void Cell::componentLeft(){
    if(overlapComponent){
        displayComponent = overlapComponent;
        overlapComponent = nullptr;
    }else {
        displayComponent = nullptr;
    }
    notifydisplay();
}

std::shared_ptr<Component> Cell::getDisplayComponent() const{ return displayComponent;}

std::shared_ptr<Component> Cell::getOverlapComponent() const{ return overlapComponent;}
