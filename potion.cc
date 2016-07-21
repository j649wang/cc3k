#include "potion.h"
#include "player.h"


using namespace std;

class player;

Potion::Potion(string name,string feature,int HPeffect,int ATKeffect,int DEFeffect,char symbol):
item(symbol), description{feature},name{name},HPeffect{HPeffect},ATKeffect{ATKeffect},DEFeffect{DEFeffect} {}

Potion::~Potion(){};

string Potion::getName() const {
    return name;
}

string Potion::describe() const {return description;}

bool Potion::isPotion() const {return true;};

int Potion::getHPeffect() const {return HPeffect;}

int Potion::getATKeffect() const {return ATKeffect;}

int Potion::getDEFeffect() const {return DEFeffect;}

