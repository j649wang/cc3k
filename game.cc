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

Game::Game(std::string inputFile):
display{make_shared<Display>()},pc{make_shared<Human>()},quitprogram{false},filename{inputFile},MerchantHostile{false}, quitgame{false},floor{nullptr}{
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
            set = true;
        }else{
            display->RaceinvalidCommand();
        }
    }
   floor = make_shared<Floor>(display, pc);
}
void Game::start(){
    fstream file;
    file.open(filename);
    floor->init(file, randomgeneration);
    play(1);
    //     if((pc->isDead())||(quitprogram)||(quitgame)) break;
    // }
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
        if(cin.eof()) break;
        
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
        }else if((cmd == "no")||(cmd == "ne")||(cmd == "ea")||(cmd == "se")||
                 (cmd == "so")||(cmd == "sw")||(cmd == "we")||(cmd == "we")){
            successMove = pcMove(cmd);
        }else {
            cout << "Invalid Command" << endl;
        }
        
        if(!successMove){
            display->failedMessage(cmd);
        }else {
            floor->EnemiesTurn(MerchantHostile);
        }
        pos = &floor->getGrid()[pc->getRow()][pc->getCol()];
    }
}

bool Game::pcMove(string dir){
    Cell *curCell = &floor->getGrid()[pc->getRow()][pc->getCol()];
    Cell *targetCell= curCell->getneighbors()[dir];
    cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
    cout << "curCell oc"  << curCell->getOverlapComponent() << endl;
    cout << "targetCell dc"  << targetCell->getDisplayComponent() << endl;
    cout << "targetCell oc"  << targetCell->getOverlapComponent() << endl;
    vector<shared_ptr <Gold>> Golds = floor->getGolds();
    bool successMove;
    if(targetCell){
        if(!targetCell->canPcWalk()){
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
            cout << "Calling Player::Move" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            pc->move(targetCell, curCell);
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            cout << "Exiting Player::Move" << endl;
            
            cout << "Calling Display::MoveMessage" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            display->moveMessage(dir);
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            cout << "Exiting Display::MoveMessage" << endl;
            
            cout << "Calling Cell::findPotions" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            vector<shared_ptr<Potion>> potions = targetCell->findPotions();
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            cout << "Exiting Cell::findPotions" << endl;
            
            cout << "finish finding Potion, moved to target" << endl;
            
            cout << "Calling Display::findpotion" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            display->findPotion(PotionList, potions);
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            cout << "Exitng Display::findpotion" << endl;
            
            cout << "Calling Cell::getOverlapComponent" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            shared_ptr<Component> c = targetCell->getOverlapComponent();
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            cout << "Exitng Cell::getOverlapComponent" << endl;
            
            if(c){
                cout << "Calling Component::isGold" << endl;
                cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
                cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
                if(c->isGold()){
                    cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
                    cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
                    cout << "Exitng Component::isGold in if Clause" << endl;
                    
                    cout << "find Gold" << endl;
                    shared_ptr<Gold> g = dynamic_pointer_cast<Gold>(c);
                    
                    cout << "Calling Player::pickGold" << endl;
                    cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
                    cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
                int amount = pc->pickGold(g, targetCell);
                    cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
                    cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
                    cout << "Exiting Player::pickGold" << endl;
                    
                    cout << "Calling Display::pickGoldMessage" << endl;
                    cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
                    cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
                display->pickGoldMessage(amount);
                    cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
                    cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
                    cout << "Exiting Display::pickGoldMessage" << endl;
              }
            }
            successMove = true;
        }
    }else {
        successMove = false;
    }
    
  /*  if(successMove){
        int i = 0; //check if player is near the DragonHoards;
        for(auto g: Golds){
            cout << "the " << i <<" time";
            cout << "Start Finding Gold Pos" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell oc"  << curCell->getOverlapComponent() << endl;
            cout << "g is " << g << endl;
            int row = g->getRow();
            int col = g->getCol();
            cout << "g.row is " << g->getRow() << ", "<< "g.col is " << g->getCol() << endl;
            Cell *Goldpos = &floor->getGrid()[row][col];
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell oc"  << curCell->getOverlapComponent() << endl;
            cout << "Finishing Finding Gold Pos" << endl;
            
            cout << "Start Finding Player" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell oc"  << curCell->getOverlapComponent() << endl;
            Cell *pcCell = Goldpos->findPlayer();
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell oc"  << curCell->getOverlapComponent() << endl;
            cout << "Finishing Cell::findplayer" << endl;
            
            cout << "calling Gold::notifyDragon" << endl;
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell oc"  << curCell->getOverlapComponent() << endl;
            g->notifyDragon(pcCell);
            cout << "curCell dc"  << curCell->getDisplayComponent() << endl;
            cout << "curCell dc"  << curCell->getOverlapComponent() << endl;
            cout << "Exiting Gold::notifyDragon" << endl;
            ++i;
        }
    }*/
    return successMove;
}
            
bool Game::pcUsePotion(string dir){
    int row = pc->getRow();
    int col = pc->getCol();
    Cell *curCell = &floor->getGrid()[row][col];
    Cell *targetCell= curCell->getneighbors()[dir];
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
    Cell *targetCell= curCell->getneighbors()[dir];
    
  if(targetCell){
    shared_ptr<Component> c = targetCell->getDisplayComponent();
      if(c){
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
  }
    return false;
}
