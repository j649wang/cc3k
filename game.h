//
//  Game.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include "floor.h"
#include "player.h"
#include "display.h"
#include "cell.h"

class Game{
    bool MerchantHostile;
    std::map<std::string, int> PotionList;
    
    std::shared_ptr<Floor> floor;
    std::shared_ptr<Player> pc;
    std::shared_ptr<Display> display;
    
    void play(int floornum);
    bool quitprogram;
    bool quitgame;
    bool randomgeneration;
    std::string filename;
    
public:
    Game(std::string file);
    ~Game();
    
    bool quitGame();
    bool quitProgram();
    void start();
    bool isWin();
    bool isLost();
    
    bool pcMove(std::string dir);
    bool pcUsePotion(std::string dir);
    bool pcAttack(std::string dir);
    
    void chooserace();
    
    
};

#endif /* Game_hpp */
