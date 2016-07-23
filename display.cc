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
    cout << "Hello! Welcome to the ChamberCrawler3000 created by z6pei, j649wang, c276chen. The following text brifly introduce the game setting" << endl;
    cout << "Your score is calculated based on the gold you collect with a 500 bonus if you successfully reached the 5th Floor. Enjoy the Game" << endl;
}

void Display::EnterStairMessage(){
    action = action + ". PC must move onto the stair from the right";
}
void Display::invalidCommand(){
    action = "Invalid Command";
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
    action = "Player character has been spawned";
}

void Display::bottomMessage(int level, const shared_ptr<Player> &pc) const{
    stringstream gold;
    gold << pc->getGold();
    string firstline = "Race: "+ pc->getName()+ " Gold: " +gold.str();
    cout << firstline;
    for (int i = 0; i < Colnum - 10 - firstline.length(); ++i){
        cout << " ";
    }
    cout << "Floor: " << level << endl;
    cout << "HP: " << pc->getHP() << endl;
    cout << "Atk: " << pc->getATK() << endl;
    cout << "Def: " << pc->getDEF() << endl;
    cout << "Action: " << action << "." << endl;
}

void Display::moveMessage(string dir){
    action = "PC moves "+ dir;
}

void Display::dragonHostileMessage(){
    action = action + ". D is hostile";
}

void Display::findPotion(map<string, int> potionList, const vector<shared_ptr<Potion>> &potion) {
    if(potion.size() > 0){
        action = action + " and found";
        map<string, int> list;
        for(auto i: potion){
            string name = i->getName();
            if(potionList[name] != 0){
                ++list[name];
            }else {
                ++list["unknown"];
            }
        }
        
        for(auto p: list){
            if(p.second == 1){
                action = action + " a " + p.first +" potion";
            }else {
                stringstream number;
                number << p.second;
                action = action + " " + number.str() + " " + p.first +" potions";
            }
        }
    }
};

void Display::drinkPotionMessage(const shared_ptr<Potion> &potion){
    action = "PC uses a " + potion->getName() + " potion";
}

void Display::pickGoldMessage(int amount){
    if(amount != 0){
        action = action + " and picked gold successfully";
    }else {
        action = action + " but failed to pick gold";
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
            action = action + " and found gold";
        }else {
            action = action + " and can pick up the dragon hoard once";
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
                action = action + ". " + e.first + " dealts " + damage.str() + " damage to PC";
            }
        }
}

void Display::failedMessage(string command){
    action = "PC failed to ";
    if(command == "u"){
        action = action +"use potion";
    }else if(command == "a"){
        action = action + "attack enemy";
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
    cout << "You won!";
}
void Display::lostMessage(){
    cout << "You lost!";
}
void Display::scoreMessage(shared_ptr<Player> pc){
    stringstream score;
    score << pc->getScore();
    cout <<" Your score is " + score.str()+"." << endl;
}

void Display::enterNextLevel(){
    action = "PC entered the next level";
}
