
//
//  Floor.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef Floor_hpp
#define Floor_hpp

#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include "chamber.h"
#include "display.h"

class Cell;
class Chamber;
class Enemy;
class Potion;
class Gold;

class Floor{
    int potionTotal;
    int enemyTotal;
    int goldTotal;
    std::shared_ptr<Player> pc;
    std::shared_ptr<Display> thedisplay;
    std::vector<std::vector<Cell>> theGrid;
    std::vector<Chamber> theChambers{5};
    std::vector<std::shared_ptr<Enemy>> theEnemys;
    std::vector<std::shared_ptr<Potion>> thePotions;
    std::vector<std::shared_ptr<Gold>> theGolds;
public:
    Floor(std::shared_ptr<Display> display,std::shared_ptr<Player> pc);
    ~Floor();
    void init(std::fstream &file, bool randomgeneration);
    void setcomponent();
    
    void generateEnemy();
    void generatePotion();
    void generateGold();
    int generatePC();
    void generateStair(int i);
    
    bool pcMove(std::string dir, std::map<std::string, int> PotionList);
    std::shared_ptr<Potion> pcUsePotion(std::string dir);
    std::shared_ptr<Enemy> pcAttack(std::string dir);
    
    
    Cell *findrandomCell(int avoid);
    int findChamber(int avoid);
    std::vector<std::vector<Cell>> getGrid();
    std::vector<std::pair<char, int>> EnemiesTurn(bool merchanthostile);
};

#endif /* Floor_hpp */