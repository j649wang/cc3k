#include "player.h"
#include "gold.h"
#include "cell.h"
#include "potion.h"
#include "enemy.h"
#include <algorithm>
#include "display.h"

using namespace std;

Player::Player(int HP,int ATK,int DEF,string name, char symbol):
Character(HP, ATK, DEF, symbol), attacked{false}, name{name} {}

Player::~Player(){};

void Player::setAtkDef() {
    setATK(getOrigATK());
    setDEF(getOrigDEF());
};

bool Player::haveAttacked(){return attacked;}

void Player::did_attack(){attacked = true;}

void Player::reset(){ attacked = false;}

bool Player::isPlayer() const{ return true;}

string Player::getName(){ return name;}

void Player::drinkPotion(shared_ptr<Potion> p, Cell *targetcell){
	setHP(getHP() + p->getHPeffect());
    setATK(getATK() + p->getATKeffect());
    setDEF(getDEF() + p->getDEFeffect());
    targetcell->componentLeft();
    cout << "potion left" << endl;
}

int Player::pickGold(shared_ptr<Gold> g, Cell *curcell){
    if(g->canPickUp()){
        setGold(getGold() + g->getValue());
        curcell->setOverlapComponent(nullptr); 
        return g->getValue();
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
    return getGold();
}
bool Player::hasReachedStair(Cell *targetcell){
    return targetcell->getSymbol() == '\\';
}