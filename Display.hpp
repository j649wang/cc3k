//
//  Display.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include <iostream>
#include <vector>
#include "Cell.hpp"
#include <string>
#include <map>

class Floor;
class Player;
class Potion;
class Cell;

const int Rownum = 25;
const int Colnum = 79;

class Display{
    int rownum;
    int colnum;
    std::string action;
    std::vector<std::vector<char>> board{Rownum, std::vector<char>{Colnum}};
public:
    Display();
    ~Display();
    void notify(const std::shared_ptr<Cell> &c);

    void beginMessage();
    void chooseRaceMessage();
    void spawnMessage();
    void enterNextLevel();
    void bottomMessage(int level, const std::shared_ptr<Player> &pc);
    
    void moveMessage(std::string dir);
    void findPotion(const std::vector<std::shared_ptr<Potion>> &potion);
    void pickGoldMessage(int amount = 0);
    
    void drinkPotionMessage(const std::shared_ptr<Potion> &potion);
    void PcAttackMessage(int damage, const std::shared_ptr<Enemy> &e);
    void EnemyAttackMessage(const std::map<std::string, int> &enemylist);
    
    void failedMessage(std::string command);
    friend std::ostream&operator<<(std::ostream &out, const shared_ptr<Display>&display);
    
};
#endif /* Display_hpp */
