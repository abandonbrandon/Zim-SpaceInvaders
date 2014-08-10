//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "BombShot.hpp"

BombShot::BombShot (Tuple* pos, Tuple* dir) : Projectile (pos,dir) {

  this->setIndex (11);
  this->setDmg (1);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

BombShot::BombShot (Tuple pos, Tuple dir) : Projectile (pos,dir) {

  this->setIndex (11);
  this->setDmg (1);
  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void BombShot::draw (void) const {

  mvaddch (this->getPos (false),this->getPos (true),'*');
  
}

//------------------------------------------------------------------------------

void BombShot::DmgArea (List* &area) const {

  Tuple tmp[11];
  int ypos = this->getPos (false);
  int xpos = this->getPos (true);
  
  for (int a (0);a<11;a++)
    tmp[a] = Tuple (ypos,xpos-5+a);

  area = new List (tmp,11);
  
}
