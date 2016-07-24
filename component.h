 #ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <memory>

class Cell;
class Component{
    int row;
    int col;
	char symbol;
  public:
    int getRow() const;
    int getCol() const;
    char getSymbol() const;
    
    void setRow(int i);
    void setCol(int j);
    void setCoords(const Cell &c);
    Component(char symbol);
    virtual ~Component() = 0;
    virtual bool isEnemy() const;
    virtual bool isGold() const;
    virtual bool isPotion() const;
    virtual bool isPlayer() const;
    virtual bool isMerchant() const;
    virtual bool isDragon() const;
    virtual void setHostile(bool hostile);
};
#endif
