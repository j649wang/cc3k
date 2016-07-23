#include "character.h"
#include <math.h>
#include "cell.h"
using namespace std;


Character::Character(int HP, int ATK, int DEF, char symbol, int gold):
Component(symbol), HP{HP},maxHP{HP}, ATK{ATK}, origATK{ATK}, DEF{DEF}, origDEF{DEF}, gold{gold}{}

void Character::setATK(int atk){
    ATK = max(0, atk);
}
void Character::setDEF(int def){
    DEF = max(0, def);
}
void Character::setHP(int hp){
    if(hp > 0){
        HP = min(hp, maxHP);
    }else {
         HP = max(hp, 0);
    }
}
void Character::setGold(int g){
    double goldnum = Character::getGold();
    gold = goldnum + g;
}

double Character::getGold() const{ return gold;}

int  Character::getATK() const{ return ATK;}

int  Character::getDEF() const{ return DEF;}

int  Character::getOrigATK() const{ return origATK;}

int  Character::getOrigDEF() const{ return origDEF;}

int  Character::getHP() const{ return HP;}

bool Character::isDead() const{ return HP == 0;}

int Character::attack(shared_ptr<Character> defender, Cell *targetcell){
        int atk = getATK();
        int def = defender->getDEF();
        int damage = ceil((100*atk)/(100+def));
        defender->setHP(defender->getHP() - damage);
        if(defender->isDead()){ targetcell->componentLeft();}
        return damage;
}
