#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "component.h" 
#include "memory"

class Cell;

class Character: public Component{
	int HP;
    int maxHP;
	int ATK;
    int origATK;
	int DEF;
    int origDEF;
    int gold;
  public:
    Character(int HP, int ATK, int DEF, char symbol, int gold = 0);
    void setATK(int atk);
    void setDEF(int def);
    void setHP(int hp);
    void setGold(int gold);
    
    int  getATK() const;
    int  getDEF() const;
    int  getHP() const;
    int  getOrigATK() const;
    int  getOrigDEF() const;

    bool isDead() const override;
    
    virtual double getGold() const;
    virtual bool move(Cell *targetcell, Cell *curcell) = 0;
    virtual int attack(std::shared_ptr<Character> defender, Cell *targetcell);
};
#endif
