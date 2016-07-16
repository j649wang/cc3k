//
//  Game.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "Game.hpp"
#include "Floor.hpp"
#include <memory>
using namespace std;

class Player{
public:
    bool reachStairs(){
        return getcell()->getneighbors[3]->getchar() == '\\';
    };
};
                
class Human: public Player{
public:
    Human();
};


Game::Game(): display{make_shared<Display>()},pc{new Human()}, quit{false},in{0}{};

Game::~Game(){}

bool Game::isWin(){
    return pc->reachStairs();
}

bool Game::isLost(){
    return (pc->getHP == 0);
}

void playGame(){
    for(int i = 1; i <= targetfloor; ++i){
        if(i == 1){
            display->beginGameMassage();
            display->chooseRaceMessage();
            char race;
            cin >> race;
            if(race != 'h'){
                auto temp = pc;
                
            }
        }
    }
}