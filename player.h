 #ifndef _PLAYER_H_
#define _PLAYER_H_
#include "character.h"
#include "gold.h"
#include <memory>
#include <map>
#include <string>

class Potion;
class Enemy;

class Player: public Character, public std::enable_shared_from_this<Player>{
	bool attacked;
    std::string name;
  public:
    Player(int HP,int ATK,int DEF, std::string name, char symbol = '@');
	bool haveAttacked();
    void setAtkDef();
    void reset();
    std::string getName();
    void did_attack();
    bool isPlayer() const override;
    bool move(Cell *targetcell, Cell *curcell) override;
    virtual void drinkPotion(std::shared_ptr<Potion> p, Cell *targetcell);
    virtual int pickGold(std::shared_ptr<Gold> g, Cell *curcell);
    virtual double getScore();
    bool hasReachedStair(Cell *targetcell);
    virtual ~Player() = 0;
};

#endif
