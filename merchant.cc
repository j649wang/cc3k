#include "merchant.h"


Merchant::Merchant():Enemy(30, 70, 5,'M',4,true,false){}

bool Merchant::isHostile() const{
    return false;
}

bool Merchant::isMerchant() const{ return true;}
