
#include "game.h"
#include "floor.h"
#include "cell.h"
#include "player.h"
#include "merchant.h"
#include "human.h"
#include "elves.h"
#include "orc.h"
#include "dwarf.h"
#include "potion.h"
#include "enemy.h"
#include <memory>
using namespace std;

const int targetfloor = 5;

Game::Game(std::string inputFile):MerchantHostile{false},floor{nullptr},pc{make_shared<Human>()},
display{make_shared<Display>()},quitprogram{false},quitgame{false}, randomgeneration{false},filename{inputFile}{
    if(filename == "map.txt"){
        randomgeneration = true;
    }
};

bool Game::quitGame(){ return quitgame; }

bool Game::quitProgram() {return quitprogram;}

Game::~Game(){}

bool Game::isWin(){
    return pc->hasReachedStair();
}

bool Game::isLost(){
    return (pc->isDead());
}

void Game::chooserace(){
    display->beginMessage();
    display->chooseRaceMessage();
    bool set = false;
    while(!set){
        string cmd;
        cin >> cmd;
        if(cmd == "e"){
            pc = make_shared<Elves>();
            set = true;
        }else if(cmd == "d"){
            pc = make_shared<Dwarf>();
            set = true;
        }else if(cmd == "o"){
            pc = make_shared<Orc>();
            set = true;
        }else if(cmd == "q"){
            quitprogram = true;
            return;
        }else if(cmd == "h"){
            set = true;
        }else{
            display->RaceinvalidCommand();
        }
    }
}
void Game::start(){
    fstream file;
    file.open(filename);
    floor = make_shared<Floor>(display, pc);
    for (int i = 1; i <=targetfloor; ++i){
        pc->reset();
        floor->clear();
        floor->init(file, randomgeneration);
        play(i);
        if((pc->isDead())||(quitprogram)||(quitgame)){
            break;
        }
     }
    
    if((!quitgame)&&(!quitprogram)){
        if(isWin()){
            display->winningMessage();
        }if(isLost()){
            display->lostMessage();
        }
        display->scoreMessage(pc);
    }
}

void Game::play(int floornum){
    int init = 0;
    while(!pc->hasReachedStair()){
        cout << display;
        if(init == 0){
            if(floornum == 1){
                display->spawnMessage();
            }else {
                display->enterNextLevel();
            }
            ++ init;
        }
        display->bottomMessage(floornum, pc);
        if(isLost()) {
         break;
        }
        bool successMove = false;
        string cmd;
        cin >> cmd;
        if(cin.eof()) break;
        
        if(cmd == "u"){
            string dir;
            cin >> dir;
            if((dir != "no")&&(dir != "ne")&&(dir != "ea")&&(dir != "se")&&
               (dir != "so")&&(dir != "sw")&&(dir != "nw")&&(dir != "we")){
                display->invalidCommand();
                continue;
            }
            shared_ptr<Potion> p = floor->pcUsePotion(dir);
            if(p){
                ++PotionList[p->getName()];
                successMove = true;
            }
        }else if(cmd == "a"){
            string dir;
            cin >> dir;
            if((dir != "no")&&(dir != "ne")&&(dir != "ea")&&(dir != "se")&&
               (dir != "so")&&(dir != "sw")&&(dir != "nw")&&(dir != "we")){
                display->invalidCommand();
                continue;
            }
            shared_ptr<Enemy> e = floor->pcAttack(dir);
            if(e){
                if(e->isMerchant()){
                    MerchantHostile = true;
                }
                 successMove = true;
            }
        }else if(cmd == "q"){
            quitprogram = true;
            return;
        }else if(cmd == "r"){
            quitgame = true;
            return;
        }else if((cmd == "no")||(cmd == "ne")||(cmd == "ea")||(cmd == "se")||
                 (cmd == "so")||(cmd == "sw")||(cmd == "nw")||(cmd == "we")){
            successMove = floor->pcMove(cmd);
        }else {
            display->invalidCommand();
            continue;
        }
        
        if((!successMove)&&((cmd == "u")||(cmd == "a"))){
            display->failedMessage(cmd);
        }
        display->EnemyAttackMessage(floor->EnemiesTurn(MerchantHostile));
        display->findPotion(PotionList, floor->findPotion());
    }
}

