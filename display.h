//
//  Display.hpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp
#include <memory>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>


class Player;
class Potion;
class Cell;
class Enemy;

const int Rownum = 25;
const int Colnum = 79;

class Display{
    int rownum;
    int colnum;
    std::string action;
    std::vector<std::vector<char>> board;
public:
    Display();
    ~Display();
    void notify(const Cell &c);

    void beginMessage();//
    void chooseRaceMessage();//
    void spawnMessage();//
    void enterNextLevel();//
    void EnterStairMessage();
    void bottomMessage(int level, const std::shared_ptr<Player> &pc); //
    
    void moveMessage(std::string dir);//
    void findPotion(std::map<std::string, int> potionList,
                    const std::vector<std::shared_ptr<Potion>> &potion); //
    void pickGoldMessage(int amount = 0);
    
    void winningMessage();//
    void lostMessage();//
    void scoreMessage(std::shared_ptr<Player> pc);//
    
    void drinkPotionMessage(const std::shared_ptr<Potion> &potion); //
    void PcAttackMessage(int damage, const std::shared_ptr<Enemy> &e); //
    void EnemyAttackMessage(const std::vector<std::pair<char, int>> &enemylist);
    
    void failedMessage(std::string command); //
    
    void RaceinvalidCommand(); //
    friend std::ostream&operator<<(std::ostream &out, const std::shared_ptr<Display>& display);
    
};
#endif /* Display_hpp */
