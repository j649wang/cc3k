//
//  Display.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/14.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "Display.hpp"
#include "Cell.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

Display::Display():rownum{Rownum}, colnum{Colnum}{}

Display::~Display(){
    board.clear();
}

void Display::notify(const shared_ptr<Cell> &c){
    int row = c->getRow();
    int col = c->getCol();
    board[row][col] = c->getSymbol();
}

void Display::beginMessage(){
    cout << "Hello! Welcome to the ChamberCrawler3000 created by z6pei, j649wang, c276chen." << endl;
}

void Display::chooseRaceMessage(){
    cout << "By default, your character is Human, but you can change your race into  one of the following by entering corresponding command: " << endl;
    cout << "Enter 'h', your race remain Human(140 HP, 20 Atk, 20 Def, 50% increase in scores)" << endl;
    cout << "Enter 'e', your race become Elves(140 HP, 30 Atk, 10 Def, negative potions have positive effect)" << endl;
    cout << "Enter 'd', your race become Dwarf (100 HP, 20 Atk, 30 Def, gold is doubled in value)" << endl;
    cout << "Enter 'o', your race become Orc (180 HP, 30 Atk, 25 Def, gold is worth half value)." << endl;
    cout << "Please choose your race, or enter 'q' to exit the game" << endl;
}

void Display::spawnMessage(){
    action = "Player character has been spawned.";
}

void Display::bottomMessage(int level, const shared_ptr<Player> &pc){
    stringstream gold;
    gold << pc->getGold();
    string firstline = "Race: "+ pc->getName()+ " Gold: " +ss.str();
    for (int i = 0; i < Rownum - 10 - firstline.length(); ++i){
        cout << " ";
    }
    cout << "Floor: " << level << endl;
    cout << "HP: " << pc->getHP() << endl;
    cout << "Atk: " << pc->getATK() << endl;
    cout << "Def: " << pc->getDEF() << endl;
    cout << "Atction: " << action << "." << endl;
}

void Display::moveMessage(string dir){
    action = "PC moves "+ dir;
}

void Display::findPotion(const vector<shared_ptr<Potion>> &potion){
    if(potion.size() > 0){
        action = action + " and finds";
        map<string, int> list;
        for(int i = 0; i < potion.size(); ++i){
            ++list[potion[i]->getName()];
        }
        for(auto &p: list){
            if(p.second == 1){
                action = action + " a " + p.first +" Potion";
            }else {
                stringstream number;
                number << p.second;
                action = action + " " + number.str() + " " + p.first +" Potions";
            }
        }
    }
    
};

void Display::drinkPotionMessage(const shared_ptr<Potion> &potion){
    action = "PC uses a " + potion->getName() + " Potion";
}

void Display::pickGoldMessage(int amount){
    if(amount != 0){
        istringstream number;
        number << amount;
        action = action + " and picked "+ number.str() +" Gold";
    }
}

void Display::PcAttackMessage(int damage, const shared_ptr<Enemy> &e){
    istringstream number, life;
    number << amout;
    life << e->getHp();
    action = "PC dealts "+ number.str() + " damage to " + e->getname() +" (" +life.str() +" HP)";
    if(e->isDead()){
        number << e->getGold();
        action = action + " and killed " + e->getname() + " and get " + number.str() + " Gold"
    }
}

void Display::EnemyAttackMessage(const map<string, int> &enemylist){
    if(enemylist.size() != 0){
        for(auto &e: enemtlist){
            if(enemylist.second == 0){
                action = action + ". " + enemylist.first + " tried to attack but failed"
            }else {
                sstringstream damage;
                damage << enemylist.second;
                action = action + ". " + enemylist.first + "dealts " + damage.str() + "to PC"
            }
        }
    }
}

void Display::failedMessage(string command){
    action = "PC failed to ";
    if(command == "u"){
        action = action +"use the Potion";
    }else if(command == "a"){
        action = action + "attack the Enemy";
    }else{
        action = action + "move, if PC try to pick Gold, kill the Dragon first";
    }
}
ostream &operator<<(std::ostream &out, const shared_ptr<Display> &display){
    for(int row = 0; row < Rownum; ++row){
        for(int col = 0; col < Colnum; ++col){
            out << display->board[row][col];
        }
        out << endl;
    }
    return out;
}