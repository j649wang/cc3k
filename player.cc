#include "player.h"
#include "gold.h"
#include "potion.h"
#include "enemy.h"
#include <algorithm>

using namespace std;

Player::Player(shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF):
	 Character(cell,symbol,HP,ATK,DEF),gold{0},attacked{false} {}

void Player::setAtkDef() {
	ATK = maxATK();
	DEF = maxDEF();
};

bool Player::haveAttacted(){return attacked;}

void Player::reset(){ attacked = false;}

void Player::drinkPotion(shared_ptr<Potion> p){
	int newHP = HP + p->getHPeffect();
	int newATK = ATK + p->getATKeffect();
	int newDEF = DEF + p->getDEFeffect();
	if (newHP >=0 && newHP <= maxHP()) HP = newHP;
	else if (newHP < 0) HP=0;
	else HP = maxHP();
	if (newATK >=0) ATK = newATK;
	else if (newATK < 0) ATK = 0;
	else ATK = maxATK();
	if (newDEF >=0) DEF = newDEF;
	else if (newDEF < 0) DEF = 0;
	else DEF = maxDEF();
	++potions[p->getType()];
}

int Player::pickGold(shared_ptr<Gold> g){
	gold = gold + g->getValue();
	return g->getValue();
}

int Player::attack(shared_ptr<Enemy> e){
	int damage=0;
	damage = ceil(100.0/(100+e->getDEF()))* ATK;
	e->setHP(max(e->getHP() - damage,0));
	attacked = true;
	return damage;
}

void Player::move(shared_ptr<Cell> cell){
	if (isDead()) return;
	if (cell) setCell(cell);
}

Player::~Player() {}	
