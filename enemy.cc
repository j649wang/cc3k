#include "enemy.h"
#include <stdlib.h>
using namespace std;

Enemy::Enemy(shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF, bool moveable):Character(cell,symbol,HP,ATK,DEF),moveable{moveable}{}

void Enemy::move() {
	if (isDead()) return;
	shared_ptr<Cell> target = getCell()->findWalkable();
	if (target) {
		getCell()->setObject(nullptr);
		setCell(target);
	}
}

Enemy::~Enemy() {}
