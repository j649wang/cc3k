#include "werewolf.h"

Werewolf::Werewolf(std::shared_ptr<Cell> cell): Enemy(cell,'W',120,30,5,true,1) {}
