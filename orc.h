//

#ifndef orc_hpp
#define orc_hpp

#include "player.h"
//override getGold;
class Orc: public Player{
public:
    Orc();
    double getGold() const override;
};
#endif /* orc_hpp */
