//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "FloodShot.hpp"

FloodShot::FloodShot (Tuple* pos, Tuple* dir) : Projectile (pos,dir) {

  this->setIndex (12);
  this->setDmg (100);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

FloodShot::FloodShot (Tuple pos, Tuple dir) : Projectile (pos,dir) {

  this->setIndex (12);
  this->setDmg (100);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void FloodShot::draw (void) const {

  mvaddch (this->getPos (false),this->getPos (true),':');
  
}
