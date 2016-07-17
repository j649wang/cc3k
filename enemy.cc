#include "enemy.h"
#include "player.h"
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

Enemy::Enemy(shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF, bool moveable,int gold):
		Character(cell,symbol,HP,ATK,DEF),moveable{moveable}, gold{gold},hasmoved{false} {}

bool Enemy::moved(){return hasmoved;}

void Enemy::move() {
	shared_ptr<Cell> target = getCell()->findwalkable();
	if (target) {
		getCell()->setObject(nullptr);
		setCell(target);
		hasmoved = true;
	}
}

int Enemy::attack(shared_ptr<Player> p) {
	int damage=0;
	srand(time(NULL));
	int r = rand()%2;
	if(r==1){ 
		damage = ceil(100.0/(100+p->getDEF()))* ATK;
		p->setHP(max(0,p->getHP() - damage));
	}
	return damage;
}

int Enemy::getGold()const{return gold;}

void Enemy::reset(){hasmoved = false;}

Enemy::~Enemy() {}
