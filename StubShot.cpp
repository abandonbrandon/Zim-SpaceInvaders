//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "StubShot.hpp"

StubShot::StubShot (Tuple* pos, Tuple* dir) : Projectile (pos,dir) {

  int ran = (rand ()%4)+1;
  this->setDmg (ran);
  this->setIndex (9);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

StubShot::StubShot (Tuple pos, Tuple dir) : Projectile (pos,dir) {

  int ran = (rand ()%5)+1;
  this->setDmg (ran);
  this->setIndex (9);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void StubShot::draw (void) const {

  mvaddch (this->getPos (false),this->getPos (true),'@');
  
}
