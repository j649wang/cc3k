//
//  Floor.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include <sstream>
#include "Floor.hpp"
#include "Cell.hpp"
#include "Chamber.hpp"
#include <cstdlib>
const int floorRow = 25;
const int floorCol = 79;
using namespace std;

Floor:: Floor(std::shared_ptr<Display> display, std::shared_ptr<Player>pc):
thedisplay{display}, pc{pc}, enemynum{20}{}

Floor::~Floor(){}

void Floor::init(std::ifstream &in){
    for(int row = 0; row < floorRow; ++row){
        std::vector<std::shared_ptr<Cell>> cellrow;
        for(int col = 0; col < floorCol; ++col){
            char c;
            in >> std::noskipws >> c;
            if ((c == '|')||(c == '_')||(c == '+')||(c == '#')||(c == '.')||(c == '\\')) {
                cellrow.emplace_back(make_shared<Cell>(row, col, thedisplay, c));
            }else if(c == ' '){
                cellrow.emplace_back(nullptr);
            }else {
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
                    theGolds.emplace_back(make_shared<Normal>());
                }else if(c == '7'){
                    theGolds.emplace_back(make_shared<Small>());
                }else if(c == '8'){
                    theGolds.emplace_back(make_shared<MerchantHoard>());
                }else if(c == '9'){
                    theGolds.emplace_back(make_shared<DragonHoard>());
                }
        
                if(('0' <= c)&(c <= '5')){
                    thePotions.back()->setCell(theGrid[row][col]);
                }else if(('6' <= c)&(c <= '9')){
                    theGolds.back()->setCell(theGrid[row][col]);
                }else{
                    theEnemys.back()->setCell(theGrid[row][col]);
                }
            }
        }
        theGrid.emplace_back(cellrow);
        in.get();
    }
    
    for(int row = 1; row < floorRow - 1; ++row){      //addneighbors
        for(int col = 1; col < floorCol - 1; ++col){
            if(theGrid[row][col]){
                theGrid[row][col]->attach(theGrid[row-1][col]);
                theGrid[row][col]->attach(theGrid[row-1][col]);
                theGrid[row][col]->attach(theGrid[row-1][col]);
                theGrid[row][col]->attach(theGrid[row-1][col]);
                theGrid[row][col]->attach(theGrid[row-1][col]);
                theGrid[row][col]->attach(theGrid[row-1][col]);
                theGrid[row][col]->attach(theGrid[row-1][col]);
            }
        }
    }
    
    for(int row = 1; row < floorRow - 1; ++row){     // assign chambers
        for(int col = 1; col < floorCol - 1; ++col){
            std::shared_ptr<Cell> cell = theGrid[row][col];
            if(cell->getSymbol() == '.'){
                if((row <= 7)&&(col <= 29)){
                    cell->setchamber(0);
                    theChambers[0]->addCells(cell);
                    cell->setChamber(theChambers[0]);
                }else if(((row <= 7)&&(col >= 38))||((row <= 13)&&(col >= 11))){
                    cell->setchamber(1);
                    theChambers[1]->addCells(cell);
                    cell->setChamber(theChambers[1]);
                }else if((row >= 14)&&(col <= 25)){
                    cell->setchamber(2);
                    theChambers[2]->addCells(cell);
                    cell->setChamber(theChambers[2]);
                }else if((row <=13)&&(row >=9)&&(col <= 60)){
                    cell->setchamber(3);
                    theChambers[3]->addCells(cell);
                    cell->setChamber(theChambers[3]);
                }else if((row >= 13)&&(col >= 36)){
                    cell->setchamber(4);
                    theChambers[4]->addCells(cell);
                    cell->setChamber(theChambers[4]);
                }
            }
            
        }
    }
}


shared_ptr<Cell> findrandomCell(){
    int chambernum = rand() % thechamber.size();
    int origchamber = chamber;
    int cellnum = rand() % thechamber[chambernum].size();
    int origcellnum = cellnum;
    while(thechamber[chambernum]->cells[cellnum]->getComponent()){
        cellnum = (cellnum+1) % thechamber[chambernum].size();
        if(cellnum == origcellnum){
            chambernum = (chambernum + 1) % thechamber.size();
            cellnum = rand() % thechamber[chambernum].size();
            origcellnum = cellnum;
        }
    }
    return thechamber[chambernum]->cells[cellnum];
}

void Floor::gererateEnemy(){
    for(int i = 0; i < enemyTotal; ++i){
        shared_ptr<Cell> targetcell = findrandomCell();
        int type = rand() % 18;
        if(type < 4){
            theEnemy.emplace_back(make_shared<Werewolf>());
        }else if(type < 7){
            theEnemy.emplace_back(make_shared<Vampire>());
        }else if(type < 12){
            theEnemy.emplace_back(make_shared<Goblin>());
        }else if(type < 14){
            theEnemy.emplace_back(make_shared<Troll>());
        }else if(type < 16){
            theEnemy.emplace_back(make_shared<Phoenix>());
        }else if(type < 18){
            theEnemy.emplace_back(make_shared<Phoenix>());
        }
        theEnemy.back()->setCell(targetcell);
    }
}
void Floor::gereratePotiion(){
    for(int i = 0; i < potionTotal; ++i){
        shared_ptr<Cell> targetcell = findrandomCell();
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
        thePotions.back()->setCell(targetcell);
    }
}

void Floor::generateGold(){
    for(int i = 0; i < goldTotal; ++i){
        shared_ptr<Cell> targetcell = findrandomCell();
        int type = rand() % 8;
        if(type == 7){
            theGolds.emplace_back(make_shared<DragonHoard>());
            -- enemyTotal;
        }else if(type < 2){
            theGolds.emplace_back(make_shared<Small>());
        }else{
            theGolds.emplace_back(make_shared<Normal>());
        }
        theGolds.back()->setCell(targetcell);
    }
}

void Floor::generatePC(){
    
}
