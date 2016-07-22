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
        bool successMove = false;
        string cmd;
        cin >> cmd;
        if(cin.eof()) break;
        
        if(cmd == "u"){
            string dir;
            cin >> dir;
            shared_ptr<Potion> p = floor->pcUsePotion(dir);
            if(p){
                ++PotionList[p->getName()];
                successMove = true;
            }
            
        }else if(cmd == "a"){
            string dir;
            cin >> dir;
            shared_ptr<Enemy> e = floor->pcAttack(dir);
            if(e){
                if(e->isMerchant()){
                    MerchantHostile = true;
                }
                 successMove = true;
            }
        }else if(cmd == "q"){
            quitprogram = true;
            return;
        }else if(cmd == "r"){
            quitgame = true;
            return;
        }else if((cmd == "no")||(cmd == "ne")||(cmd == "ea")||(cmd == "se")||
                 (cmd == "so")||(cmd == "sw")||(cmd == "nw")||(cmd == "we")){
            successMove = floor->pcMove(cmd, PotionList);
        }else {
            display->invalidCommand();
            continue;
        }
        
        if(!successMove){
            display->failedMessage(cmd);
        }else {
            floor->EnemiesTurn(MerchantHostile);
        }
        
        pos = &floor->getGrid()[pc->getRow()][pc->getCol()];
    }
}

