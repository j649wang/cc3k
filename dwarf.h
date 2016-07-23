
#ifndef dwarf_hpp
#define dwarf_hpp

#include "player.h"
//override getGold;
class Dwarf: public Player{
public:
    Dwarf();
    double getGold() const override;
};
#endif /* dwarf_hpp */
