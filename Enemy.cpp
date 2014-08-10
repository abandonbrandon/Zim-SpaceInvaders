//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Enemy.hpp"

Enemy::Enemy (Tuple* pos, int HP) : Agent (pos,HP) {}

//------------------------------------------------------------------------------

Enemy::Enemy (Tuple pos, int HP) : Agent (pos,HP) {}

//------------------------------------------------------------------------------

Enemy::Enemy (Tuple* pos) : Agent (pos) {}

//------------------------------------------------------------------------------

int Enemy::getScore (void) const {

  return score;
  
}

//------------------------------------------------------------------------------

void Enemy::setScore (int scr) {

  score = scr;
  
}
