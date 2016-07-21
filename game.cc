//
//  Game.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "game.h"
#include "floor.h"
#include "cell.h"
#include "player.h"
#include "merchant.h"
#include "human.h"
#include "elves.h"
#include "orc.h"
#include "dwarf.h"
#include "potion.h"
#include "enemy.h"
#include <memory>
using namespace std;

const int targetfloor = 5;
int dirConvert(string dir){
    int index;
    if(dir == "no") index = 0;
    else if(dir == "ne") index = 1;
    else if(dir == "ea") index = 2;
    else if(dir == "se") index = 3;
    else if(dir == "so") index = 4;
    else if(dir == "sw") index = 5;
    else if(dir == "we") index = 6;
    else if(dir == "nw") index = 7;
    return  index;
}

Game::Game(const std::string inputFile):
display{make_shared<Display>()},pc{make_shared<Human>()},
quitprogram{false},filename{inputFile},floor{nullptr},
MerchantHostile{false}, quitgame{false}{
    if(filename == "map.txt"){
        randomgeneration = true;
    }
};

bool Game::quitGame(){ return quitgame; }

bool Game::quitProgram() {return quitprogram;}

Game::~Game(){}

bool Game::isWin(){
    int row = pc->getRow();
    int col = pc->getCol();
    return pc->hasReachedStair(&floor->getGrid()[row][col]);
}

bool Game::isLost(){
    return (!pc->isDead());
}

void Game::chooserace(){
    display->beginMessage();
    display->chooseRaceMessage();
    bool set = false;
    while(!set){
        string cmd;
        cin >> cmd;
        if(cmd == "e"){
            pc = make_shared<Elves>();
            set = true;
        }else if(cmd == "d"){
            pc = make_shared<Dwarf>();
            set = true;
        }else if(cmd == "o"){
            pc = make_shared<Orc>();
            set = true;
        }else if(cmd == "q"){
            quitprogram = true;
            return;
        }else if(cmd == "h"){
            return;
        }else{
            display->RaceinvalidCommand();
        }
    }
}
            
bool Game::pcMove(string dir){
    int row = pc->getRow();
    int col = pc->getCol();
    Cell *curCell = &floor->getGrid()[row][col];
    Cell *targetCell= curCell->getneighbors()[dirConvert(dir)];
    vector<shared_ptr <Gold>> Golds = floor->getGolds();
    bool successMove;
    if((!targetCell)||(!targetCell->canPcWalk())){
      successMove = false;
    }else if(targetCell->getSymbol() == '\\'){
        if(dir == "we"){
            pc->move(targetCell, curCell);
            successMove = true;
        }else{
            display->EnterStairMessage();
            successMove = false;
        }
    }else {
        vector<shared_ptr<Potion>> potions = targetCell->findPotions();
        pc->move(targetCell, curCell);
        display->moveMessage(dir);
        display->findPotion(PotionList, potions);
        shared_ptr<Component> c = targetCell->getOverlapComponent();
        if(c->isGold()){
          shared_ptr<Gold> g = dynamic_pointer_cast<Gold>(c);
          int amount = pc->pickGold(g, targetCell);
          display->pickGoldMessage(amount);
        }
        successMove = true;
    }
    
    if(successMove){         //check if player is near the DragonHoards;
        for(auto g: Golds){
            Cell *Goldpos = &floor->getGrid()[g->getRow()][g->getCol()];
            g->notifyDragon(Goldpos->findPlayer());
        }
    }
    return successMove;
}
            
bool Game::pcUsePotion(string dir){
    int row = pc->getRow();
    int col = pc->getCol();
    Cell *curCell = &floor->getGrid()[row][col];
    Cell *targetCell= curCell->getneighbors()[dirConvert(dir)];
  if(targetCell){
    shared_ptr<Component> c = targetCell->getDisplayComponent();
    if(c->isPotion()){
        shared_ptr<Potion> p =dynamic_pointer_cast<Potion>(c);
        ++PotionList[p->getName()];
        pc->drinkPotion(p, targetCell);
        display->drinkPotionMessage(p);
      return true;
    }
  }
     return false;
}

bool Game::pcAttack(string dir){
    int row = pc->getRow();
    int col = pc->getCol();
    Cell *curCell = &floor->getGrid()[row][col];
    Cell *targetCell= curCell->getneighbors()[dirConvert(dir)];
    
  if(targetCell){
    shared_ptr<Component> c = targetCell->getDisplayComponent();
    if(c->isEnemy()){
        shared_ptr<Enemy> e = dynamic_pointer_cast<Enemy>(c);
        int damage = pc->attack(e, targetCell);
        display->PcAttackMessage(damage, e);
        if(e->isMerchant()){
            MerchantHostile = true;
        }
        pc->did_attack();
      return true;
    }
  }
    return false;
}

void Game::start(){
    fstream file;
    file.open(filename);
    for(int i = 1; i <= targetfloor; ++i){
        floor = make_shared<Floor>(display, pc);
        floor->init(file, randomgeneration);
        cout << display;
        play(i);
        if((pc->isDead())||(quitprogram)||(quitgame)) break;
    }
    if((!quitgame)||(!quitprogram)){
        if(isWin()){
            display->winningMessage();
        }else{
            display->lostMessage();
        }
        display->scoreMessage(pc);
    }
}

void Game::play(int floornum){
    int init = 0;
    Cell *pos = &floor->getGrid()[pc->getRow()][pc->getCol()];
    while(!isLost()||!pc->hasReachedStair(pos)){
        cout << display;
        if(init == 0){
            if(floornum == 1){
                display->spawnMessage();
            }else {
                display->enterNextLevel();
            }
            ++ init;
        }
        display->bottomMessage(floornum, pc);
        bool successMove;
        string cmd;
        cin >> cmd;
        if(cmd == "u"){
            string dir;
            cin >> dir;
            successMove = pcUsePotion(dir);
        }else if(cmd == "a"){
            string dir;
            cin >> dir;
            successMove = pcAttack(dir);
        }else if(cmd == "q"){
            quitprogram = true;
            return;
        }else if(cmd == "r"){
            quitgame = true;
            return;
        }else {
            successMove = pcMove(cmd);
        }
        if(!successMove){
            display->failedMessage(cmd);
        }else {
            floor->EnemiesTurn(MerchantHostile);
        }
        pos = &floor->getGrid()[pc->getRow()][pc->getCol()];
    }
}