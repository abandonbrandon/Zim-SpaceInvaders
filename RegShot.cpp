//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "RegShot.hpp"

RegShot::RegShot (Tuple* pos, Tuple* dir) : Projectile (pos,dir) {

  this->setIndex (7);
  this->setDmg (1);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

RegShot::RegShot (Tuple pos, Tuple dir) : Projectile (pos,dir) {

  this->setIndex (7);
  this->setDmg (1);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void RegShot::draw (void) const {

  mvaddch (this->getPos (false),this->getPos (true),'!');
  
}
