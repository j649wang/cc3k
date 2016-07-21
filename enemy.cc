#include "enemy.h"
#include "player.h"
#include "cell.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

Enemy::Enemy(int HP,int ATK,int DEF, char symbol, int gold, bool moveable, bool isHostile):
Character(HP,ATK,DEF,symbol,gold),moveable{moveable},ishostile{isHostile} {}

Enemy::~Enemy(){};

void Enemy::setHostile(bool i){
    ishostile = i;
}

bool Enemy::isHostile() const{
    return ishostile;
}


bool Enemy::canMove() const{ return moveable;}


bool Enemy::move(Cell *targetcell, Cell *curcell){
    if(targetcell){
        setCoords(*targetcell);
        targetcell->setDisplayComponent(shared_from_this());
        curcell->componentLeft();
        return true;
    }
    return false;
}

int Enemy::attack(std::shared_ptr<Character> defender, Cell *targetcell) {
    int r = rand()%2;
        if(r == 1){
            return Character::attack(defender, targetcell);
        }else {
            return 0;
        }
}

bool Enemy::isEnemy() const{ return true;}
