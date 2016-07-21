#include "dragonHoard.h"
#include "character.h"
#include "cell.h"
using namespace std;

DragonHoard::DragonHoard(): Gold(6),guard{nullptr}{}

void DragonHoard::notifyDragon(Cell *Playernear){
    if(Playernear){
        guard->setHostile(true);
    }else {
        guard->setHostile(false);
    }
}
void DragonHoard::addDragon(Cell *curpos){
    shared_ptr<Component> d = curpos->findDragon();
    setGuard(d);
}

void DragonHoard::setGuard(shared_ptr<Component> dragon){
    guard = dragon;
}

bool DragonHoard::canPickUp() const{
    return guard->isDead();
};