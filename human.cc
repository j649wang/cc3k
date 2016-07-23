#include "human.h"

Human::Human(): Player(140, 20, 20, "Human") {}

int Human::getScore(){
   int score = Player::getScore();
   return 1.5*score;
}
