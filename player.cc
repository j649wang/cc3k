#include "player.h"
#include "gold.h"
#include "potion.h"

using namespace std;

Player::Player(shared_ptr<Cell> cell, char symbol, int HP, int ATK, int DEF,int wealth): Character(cell,symbol,HP,ATK,DEF),wealth{wealth} {}

void Player::setAtkDef() {
	ATK = maxATK();
	DEF = maxDEF();
};

void Player::drinkPotion(Potion &p){
	int newHP = HP + p.getHPeffect();
	int newATK = ATK + p.getATKeffect();
	int newDEF = DEF + p.getDEFeffect();
	if (newHP >=0 && newHP <= maxHP()) HP = newHP;
	else if (newHP < 0) HP=0;
	else HP = maxHP();
	if (newATK >=0 && newATK <= maxATK()) ATK = newATK;
	else if (newATK < 0) ATK = 0;
	else ATK = maxATK();
	if (newDEF >=0 && newDEF <= maxDEF()) DEF = newDEF;
	else if (newDEF < 0) DEF = 0;
	else DEF = maxDEF();
}

void Player::pickGold(Gold &g){
	wealth = wealth + g.getValue();
}

void Player::move(shared_ptr<Cell> cell){
	if (isDead()) return;
	if (cell) setCell(cell);
}

Player::~Player() {}	
