#include "player.h"
#include "gold.h"
#include "cell.h"
#include "potion.h"
#include "enemy.h"
#include <algorithm>
#include "display.h"

using namespace std;

Player::Player(int HP,int ATK,int DEF,string name, char symbol):
Character(HP, ATK, DEF, symbol), name{name},reachedStair{false}{}

Player::~Player(){};

void Player::reset() {
    setATK(getOrigATK());
    setDEF(getOrigDEF());
    reachedStair = false;
};


bool Player::isPlayer() const{ return true;}

string Player::getName(){ return name;}

void Player::drinkPotion(shared_ptr<Potion> p, Cell *targetcell){
	setHP(getHP() + p->getHPeffect());
    setATK(getATK() + p->getATKeffect());
    setDEF(getDEF() + p->getDEFeffect());
    targetcell->componentLeft();

}

int Player::pickGold(shared_ptr<Gold> g, Cell *curcell){
    if(g->canPickUp()){
        int amount = g->getValue();
        setGold(Character::getGold() + g->getValue());
        curcell->setOverlapComponent(nullptr);
        g->setValue(0);
        return amount;
    }
    return 0;
}

bool Player::move(Cell *targetcell, Cell *curcell){
    if(targetcell->getDisplayComponent()){
        shared_ptr<Component> dc= targetcell->getDisplayComponent();
        if(dc->isGold()){
            targetcell->setOverlapComponent(dc);
            // set gold as the overlap Component;
        }
    }
    setCoords(*targetcell);
    targetcell->setDisplayComponent(shared_from_this());
    curcell->componentLeft();
    return true;
}

double Player::getScore() {
    if(reachedStair){
        return getGold()*1000 + 500;
    }else {
        return getGold()*1000;
    }
}

bool Player::hasReachedStair() const{
    return reachedStair;
}

void Player::setReachedStair(){
    reachedStair = true;
}
