//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "TriShot.hpp"

TriShot::TriShot (Tuple* pos, Tuple* dir) : Projectile (pos,dir) {

  this->setIndex (8);
  this->setDmg (1);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

TriShot::TriShot (Tuple pos, Tuple dir) : Projectile (pos,dir) {

  this->setIndex (8);  
  this->setDmg (1);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void TriShot::draw (void) const {

  mvaddch (this->getPos (false),this->getPos (true),'^');
  
}
