#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "enemy.h"

class Merchant: public Enemy{  
public:
    Merchant();
    bool isHostile() const override;
    bool isMerchant() const override;//override;
};
#endif
