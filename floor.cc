//
//  Floor.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include <sstream>
#include <fstream>
#include "floor.h"
#include "cell.h"
#include "chamber.h"
#include "rh.h"
#include "ph.h"
#include "ba.h"
#include "wa.h"
#include "bd.h"
#include "wd.h"
#include "dragonHoard.h"
#include "normalHoard.h"
#include "smallHoard.h"
#include "merchantHoard.h"
#include "merchant.h"
#include "vampire.h"
#include "phoenix.h"
#include "troll.h"
#include "goblin.h"
#include "werewolf.h"
#include "dragon.h"
#include "player.h"
#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>

const int floorRow = 25;
const int floorCol = 79;
using namespace std;

Floor:: Floor(shared_ptr<Display> display,shared_ptr<Player> pc):
thedisplay{display},pc{pc}, enemyTotal{20},potionTotal{10},goldTotal{10}{}

Floor::~Floor(){
    theChambers.clear();
    theEnemys.clear();
    theGrid.clear();
    thePotions.clear();
    theGolds.clear();
}

void Floor::init(std::fstream &file, bool randomgeneration){
    for(int row = 0; row < floorRow; ++row){
        vector<Cell> cellrow;
        for(int col = 0; col < floorCol; ++col){
            char c;
            file >> noskipws >> c;
            if ((c == '|')||(c == '-')||(c == '+')||     //generate unoccupied floortile;
                (c == '#')||(c == '.')||(c == '\\')||(c == ' ')) {
                cellrow.emplace_back(row, col, thedisplay, c);
                cellrow[col].notifydisplay();
            }else{
                 //generate occupied floortiles
                cellrow.emplace_back(row, col, thedisplay, '.');
                if(c == '0'){
                    thePotions.emplace_back(make_shared<RH>());
                }else if(c == '1'){
                    thePotions.emplace_back(make_shared<BA>());
                }else if(c == '2'){
                    thePotions.emplace_back(make_shared<BD>());
                }else if(c == '3'){
                    thePotions.emplace_back(make_shared<PH>());
                }else if(c == '4'){
                    thePotions.emplace_back(make_shared<WA>());
                }else if(c == '5'){
                    thePotions.emplace_back(make_shared<WD>());
                }else if(c == '6'){
                    theGolds.emplace_back(make_shared<NormalHoard>());
                }else if(c == '7'){
                    theGolds.emplace_back(make_shared<SmallHoard>());
                }else if(c == '8'){
                    theGolds.emplace_back(make_shared<MerchantHoard>());
                }else if(c == '9'){
                    theGolds.emplace_back(make_shared<DragonHoard>());
                }else if(c == 'V'){
                    theEnemys.emplace_back(make_shared<Vampire>());
                }else if(c == 'W'){
                    theEnemys.emplace_back(make_shared<Werewolf>());
                }else if(c == 'N'){
                    theEnemys.emplace_back(make_shared<Goblin>());
                }else if(c == 'M'){
                    theEnemys.emplace_back(make_shared<Merchant>());
                }else if(c == 'D'){
                    theEnemys.emplace_back(make_shared<Dragon>());
                }else if(c == 'X'){
                    theEnemys.emplace_back(make_shared<Phoenix>());
                }else if(c == 'T'){
                    theEnemys.emplace_back(make_shared<Troll>());
                }
                
                if(('0' <= c)&(c <= '5')){
                    thePotions.back()->setRow(row);
                    thePotions.back()->setCol(col);
                    cellrow[col].setDisplayComponent(thePotions.back());
                }else if(('6' <= c)&(c <= '9')){
                    theGolds.back()->setRow(row);
                    theGolds.back()->setCol(col);
                    cellrow[col].setDisplayComponent(theGolds.back());
                }else if(c == '@'){
                    pc->setRow(row);
                    pc->setCol(col);
                    cellrow[col].setDisplayComponent(pc);
                }else if((c == 'V')||(c == 'W')||(c == 'N')||(c == 'M')||(c == 'D')||(c == 'X')||(c == 'T')){
                    theEnemys.back()->setRow(row);
                    theEnemys.back()->setCol(col);
                    cellrow[col].setDisplayComponent(theEnemys.back());
                }
            }
        }
        char white;
        file >> white;
        theGrid.emplace_back(cellrow);
    }

    
    for(int row = 0; row < floorRow; ++row){      //add neighbors
        for(int col = 0; col < floorCol; ++col){
            theGrid[row][col].attach((row-1 >= 0)? &theGrid[row-1][col]: nullptr, "no");
            theGrid[row][col].attach(((row-1 >= 0)&&(col-1 >= 0))? &theGrid[row-1][col-1]: nullptr, "nw");
            theGrid[row][col].attach((col-1 >= 0)? &theGrid[row][col-1]: nullptr, "we");
            theGrid[row][col].attach(((row+1 < floorRow)&&(col-1 >= 0))? &theGrid[row+1][col-1]:nullptr, "sw");
            theGrid[row][col].attach((row+1 < floorRow)? &theGrid[row+1][col]: nullptr, "so");
            theGrid[row][col].attach(((row+1 < floorRow)&&(col+1 <floorCol))?&theGrid[row+1][col+1]: nullptr, "se");
            theGrid[row][col].attach((col+1 < floorCol)?&theGrid[row][col+1]: nullptr, "ea");
            theGrid[row][col].attach(((row-1 >= 0)&&(col-1 >= 0))? &theGrid[row-1][col+1]: nullptr, "ne");
        }
    }
    
    for(int row = 0; row < floorRow; ++row){     // assign chambers
        for(int col = 0; col < floorCol; ++col){
            Cell *cell = &theGrid[row][col];
            if((cell->getTileSymbol() == '.')&&(cell->getChamber() == -1)){
                if((row <= 7)&&(col <= 29)){
                    cell->setChamber(0);
                    theChambers[0].addCells(cell);
                }else if(((row <= 7)&&(col >= 38))||((row <= 13)&&(col >= 60))){
                        cell->setChamber(1);
                        theChambers[1].addCells(cell);
                }else if((row >= 14)&&(col <= 25)){
                    cell->setChamber(2);
                    theChambers[2].addCells(cell);
                }else if((row <=13)&&(row >=9)&&(col <= 60)){
                    cell->setChamber(3);
                    theChambers[3].addCells(cell);
                }else if((row > 13)&&(col >= 36)){
                    cell->setChamber(4);
                    theChambers[4].addCells(cell);
                }
            }
            
        }
    }
    if(randomgeneration){
        setcomponent();
    }
}

int Floor::findChamber(int avoid){
    int chambernum = rand() % theChambers.size();
    while(chambernum == avoid){
        chambernum = rand()  % theChambers.size();
    }
    return chambernum;
}

Cell *Floor::findrandomCell(int avoid){
    int chambernum = findChamber(avoid);
    vector<Cell *> curChamber = theChambers[chambernum].getCells();
    int cellnum = rand() % curChamber.size();
    
    Cell *targetcell = curChamber[cellnum];
    while(targetcell->getDisplayComponent() || targetcell->getSymbol() == '\\'){
        chambernum = findChamber(avoid);
        curChamber = theChambers[chambernum].getCells();
        cellnum = rand() % curChamber.size();
        targetcell = curChamber[cellnum];
    }
    return theChambers[chambernum].getCells()[cellnum];
}

void Floor::generateEnemy(){
    for(int i = 0; i < enemyTotal; ++i){
        Cell *targetcell = findrandomCell(-1);
        int type = rand() % 18;
        if(type < 4){
            theEnemys.emplace_back(make_shared<Werewolf>());
        }else if(type < 7){
            theEnemys.emplace_back(make_shared<Vampire>());
        }else if(type < 12){
            theEnemys.emplace_back(make_shared<Goblin>());
        }else if(type < 14){
            theEnemys.emplace_back(make_shared<Troll>());
        }else if(type < 16){
            theEnemys.emplace_back(make_shared<Phoenix>());
        }else if(type < 18){
            theEnemys.emplace_back(make_shared<Merchant>());
        }
        theEnemys.back()->setCoords(*targetcell);
        targetcell->setDisplayComponent(theEnemys.back());
    }
}
void Floor::generatePotion(){
    for(int i = 0; i < potionTotal; ++i){
        Cell *targetcell = findrandomCell(-1);
        int type = rand() % 6;
        if(type == 0){
            thePotions.emplace_back(make_shared<RH>());
        }else if(type == 1){
            thePotions.emplace_back(make_shared<BA>());
        }else if(type == 2){
            thePotions.emplace_back(make_shared<BD>());
        }else if(type == 3){
            thePotions.emplace_back(make_shared<PH>());
        }else if(type == 4){
            thePotions.emplace_back(make_shared<WA>());
        }else if(type == 5){
            thePotions.emplace_back(make_shared<WD>());
        }
        thePotions.back()->setCoords(*targetcell);
        targetcell->setDisplayComponent(thePotions.back());
    }
}

void Floor::generateGold(){
    for(int i = 0; i < goldTotal; ++i){
        Cell *targetcell = findrandomCell(-1);
        int gtype = rand() % 8;
        if(gtype == 7){
            theGolds.emplace_back(make_shared<DragonHoard>());
            theEnemys.emplace_back(make_shared<Dragon>());
            theGolds.back()->setGuard(theEnemys.back());
            -- enemyTotal;
            
            cout << "generate a Dragon Hoard, should find a D nearby" << endl;
            Cell *dragonPos = targetcell->findWalkable();
            theEnemys.back()->setCoords(*dragonPos);
            dragonPos->setDisplayComponent(theEnemys.back());
        }else if(gtype < 2){
            theGolds.emplace_back(make_shared<SmallHoard>());
        }else{
            theGolds.emplace_back(make_shared<NormalHoard>());
        }
        theGolds.back()->setCoords(*targetcell);
        targetcell->setDisplayComponent(theGolds.back());
    }
}

int Floor::generatePC(){
    Cell *targetcell = findrandomCell(-1);
    pc->setCoords(*targetcell);
    targetcell->setDisplayComponent(pc);
    return targetcell->getChamber();
}

void Floor::generateStair(int avoid){
    Cell *targetcell = findrandomCell(avoid);
    targetcell->setSymbol('\\');
}

void Floor::setcomponent(){
    int avoid = generatePC();
    cout << pc->getName() << endl;
    generateStair(avoid);
    generatePotion();
    generateGold();
    generateEnemy();
    
}

vector<pair<char, int>> Floor::EnemiesTurn(bool merchanthostile){
    vector<pair<char, int>> enemyAttack;
    sort(theEnemys.begin(),theEnemys.end(),     //sort the theEnemy line by line fashion
         [] (const shared_ptr<Enemy>& e1, const shared_ptr<Enemy>& e2){
             if(e1->getRow() < e2->getRow()){
                 return true;
             }else if(e1->getRow()  == e2->getRow()){
                 return e1->getCol()  < e2->getCol();
             }else{
                 return false;
             }
         });
    for(auto e: theEnemys){
        Cell *curCell = &theGrid[e->getRow()][e->getCol()];
        cout << "Enemy: " << curCell << endl;
        Cell *playerCell = curCell->findPlayer();
        cout << "Enemy: playercell" << playerCell << endl;
        Cell *walkCell = curCell->findWalkable();
        cout << "Enemy: walkCell " << walkCell << endl;
        
        if(!e->isDead()){
            if((pc->haveAttacked())&&(playerCell)){
                if((e->isMerchant()&& merchanthostile)||(e->isHostile())){
                    int damage = e->attack(pc, playerCell);
                    enemyAttack.emplace_back(make_pair(e->getSymbol(), damage));
                }
            }else if(e->canMove()){
                e->move(walkCell, curCell);
                enemyAttack.emplace_back(make_pair(e->getSymbol(), -1));
            }
        }
    }
    pc->reset();
    return enemyAttack;
}

bool Floor::pcMove(string dir, map<string, int> PotionList){
    bool moveSuccess = false;
    Cell *curCell = &theGrid[pc->getRow()][pc->getCol()];
    Cell *targetCell= curCell->getneighbors()[dir];
    if(targetCell){
        if(!targetCell->canPcWalk()){
            return false;
        }else if(targetCell->getSymbol() == '\\'){
            if(dir == "we"){
                pc->move(targetCell, curCell);
                moveSuccess = true;
            }else{
                thedisplay->failedMessage(dir);
                thedisplay->EnterStairMessage();
                return false;
            }
        }else {
            pc->move(targetCell, curCell);
            thedisplay->moveMessage(dir);
            vector<shared_ptr<Potion>> potions = targetCell->findPotions();
            thedisplay->findPotion(PotionList, potions);
            shared_ptr<Component> c = targetCell->getOverlapComponent();
            if(c){
                if(c->isGold()){
                    cout << "ready to pick Gold" << endl;
                    shared_ptr<Gold> g = dynamic_pointer_cast<Gold>(c);
                    int amount = pc->pickGold(g, targetCell);
                    thedisplay->pickGoldMessage(amount);
                }
            }
            moveSuccess = true;
        }
    }
    if(moveSuccess){
        for(auto g: theGolds){
              int row = g->getRow();
              int col = g->getCol();
              Cell *Goldpos = &theGrid[row][col];
              Cell *pcCell = Goldpos->findPlayer();
            if(pcCell){
             thedisplay->dragonHostileMessage();
            }
              g->notifyDragon(pcCell);
          }
     }
    return moveSuccess;
}

shared_ptr<Potion> Floor::pcUsePotion(string dir){
    int row = pc->getRow();
    int col = pc->getCol();
    Cell *curCell = &theGrid[row][col];
    Cell *targetCell= curCell->getneighbors()[dir];
    if(targetCell){
        shared_ptr<Component> c = targetCell->getDisplayComponent();
        if(c->isPotion()){
            shared_ptr<Potion> p =dynamic_pointer_cast<Potion>(c);
            pc->drinkPotion(p, targetCell);
            thedisplay->drinkPotionMessage(p);
            return p;
        }
    }
    return nullptr;
}

shared_ptr<Enemy> Floor::pcAttack(string dir){
    int row = pc->getRow();
    int col = pc->getCol();
    Cell *curCell = &theGrid[row][col];
    Cell *targetCell= curCell->getneighbors()[dir];
    
    if(targetCell){
        shared_ptr<Component> c = targetCell->getDisplayComponent();
        if(c){
            if(c->isEnemy()){
                shared_ptr<Enemy> e = dynamic_pointer_cast<Enemy>(c);
                int damage = pc->attack(e, targetCell);
                thedisplay->PcAttackMessage(damage, e);
                pc->did_attack();
                return e;
            }
        }
    }
    return nullptr;
}

vector<vector<Cell>> Floor::getGrid(){ return theGrid; }
