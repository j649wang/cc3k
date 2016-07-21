#include "display.h"
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

Display::Display():rownum{Rownum}, colnum{Colnum}{
    for(int i = 0; i < Rownum; ++i){
        vector<char> row;
        for(int j = 0; j < Colnum; ++j){
            row.emplace_back();
        }
        board.emplace_back(row);
    }
}

Display::~Display(){
    board.clear();
}

void Display::notify(const Cell &c){
    int row = c.getRow();
    int col = c.getCol();
    board[row][col] = c.getSymbol();
}

void Display::beginMessage(){
    cout << "Hello! Welcome to the ChamberCrawler3000 created by z6pei, j649wang, c276chen." << endl;
}

void Display::EnterStairMessage(){
    action = action + ". PC must move to Stair from the right";
}

void Display::RaceinvalidCommand(){
    cout << "Invalid Command. Please enter one of 'h', 'e', 'o', 'd' or 'q'" << endl;
}

void Display::chooseRaceMessage(){
    cout << "By default, your character is Human, but you can change your race into one of the following by entering corresponding command: " << endl;
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
    string firstline = "Race: "+ pc->getName()+ " Gold: " +gold.str();
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

void Display::findPotion(map<string, int> potionList, const vector<shared_ptr<Potion>> &potion){
    if(potion.size() > 0){
        action = action + " and finds";
        map<string, int> list;
        for(auto i: potion){
            string name = i->getName();
            if(potionList[name] != 0){
                ++list[name];
            }else {
                ++list["Unknown"];
            }
        }
        
        for(auto p: list){
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
        action = action + " and picked a pile of Gold";
    }else {
        action = action + " failed to pick Gold";
    }
}

void Display::PcAttackMessage(int damage, const shared_ptr<Enemy> &e){
    stringstream number, life;
    number << damage;
    life << e->getHP();
    action = "PC dealts "+ number.str() + " damage to " + e->getSymbol() +" (" +life.str() +" HP)";
    if(e->isDead()){
        number << e->getGold();
        action = action + " and killed " + e->getSymbol();
        if(e->getSymbol() != 'D'){
            action = action + " and found a pile of Gold";
        }else {
            action = action + " and PC may pick up the Dragon Hoard";
        }
    }
}

void Display::EnemyAttackMessage(const vector<pair<char, int>> &enemylist){
        for(auto &e: enemylist){
            if(e.second == 0){
                action = action + ". " + e.first + " tried to attack but failed";
            }else if(e.second > 0){
                stringstream damage;
                damage << e.second;
                action = action + ". " + e.first + "dealts " + damage.str() + "to PC";
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
        action = action + "move";
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
void Display::winningMessage(){
    action = "You won!";
}
void Display::lostMessage(){
    action = "You lost!";
}
void Display::scoreMessage(shared_ptr<Player> pc){
    stringstream score;
    score << pc->getScore();
    action = action + " Your Score is " + score.str();
}

void Display::enterNextLevel(){
    action = "PC entered the next level";
}