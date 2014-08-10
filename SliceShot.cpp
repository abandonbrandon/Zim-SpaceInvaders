//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "SliceShot.hpp"

SliceShot::SliceShot (Tuple* pos, Tuple* dir) : Projectile (pos,dir) {

  this->setIndex (10);
  this->setDmg (100);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

SliceShot::SliceShot (Tuple pos, Tuple dir) : Projectile (pos,dir) {

  this->setIndex (10);
  this->setDmg (100);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void SliceShot::draw (void) const {

  mvaddch (this->getPos (false),this->getPos (true),'$');
  
}
