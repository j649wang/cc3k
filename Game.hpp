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

class Floor;
class Player;
class Display;

const int targetfloor = 5;

class Game{
    Floor *floor;
    Player *pc;
    std::shared_ptr<Display> display;
    void playRound(int floornum);
    bool quit;
    bool map;
    std::ifstream *in;
    
public:
    Game();
    ~Game();
    
    void playGame();
    bool isWin();
    bool isLost();
    void pcMove(std::string dir);
    void pcUsePotion(std::string dir);
    void pcAttack(std::string dir);
    void chooserace(char type);
    
    
};

#endif /* Game_hpp */
