#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "character.h"

class Player;

class Enemy: public Character, public std::enable_shared_from_this<Enemy>{
	bool moveable;
    bool ishostile;
    int gold;
  public:
    bool canMove() const;
    bool operator<(const std::shared_ptr<Enemy> &e);
    Enemy(int HP,int ATK,int DEF, char symbol, int gold = 1,
          bool moveable = true, bool isHostile = true);
	int attack(std::shared_ptr<Character> defender, Cell *targetcell) override;
	bool move(Cell *targetcell, Cell *curcell) override;
    void setHostile(bool hostile) override;
    virtual bool isHostile() const;
    bool isEnemy() const override;
    
	virtual ~Enemy() = 0;
};
#endif
