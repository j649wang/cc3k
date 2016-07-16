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
#include <stdio.h>
#include <vector>
#include <fstream>
#include "Display.hpp"


class Floor{
    int potionTotal;
    int enemyTotal;
    int goldTotal;
    std::shared_ptr<Display> thedisplay;
    std::shared_ptr<Player> pc;
    std::vector<std::vector<std::shared_ptr<Cell>>> theGrid;
    std::vector<std::shared_ptr<Chamber>> theChambers;
    std::vector<std::shared_ptr<Enemy>> theEnemys;
    std::vector<std::shared_ptr<Potion>> thePotions;
    std::vector<std::shared_ptr<Gold>> theGolds;
public:
    Floor(std::shared_ptr<Display> thedisplay,std::shared_ptr<Player> pc);
    ~Floor();
    void init(std::ifstream &in);
    void setcomponent();
    void generateEnemy();
    void generatePotion();
    void generateGold();
    void generatePC();
    void generateStair(int i);
    bool sortEnemy(const std::shared_ptr<Enemy> &e1, const std::shared_ptr<Enemy> &e2);
    void moveEnemy();
};

#endif /* Floor_hpp */
