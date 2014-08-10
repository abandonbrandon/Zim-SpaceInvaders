//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "PowerUp.hpp"
#include "FloodShot.hpp"
#include "BombShot.hpp"
#include "SliceShot.hpp"
#include "StubShot.hpp"
#include "TriShot.hpp"

PowerUp::PowerUp (Tuple* pos) : Movable (pos) {

  this->setDir (Tuple (1,0));
  
}

//------------------------------------------------------------------------------

PowerUp::PowerUp (Tuple pos) : Movable (&pos) {

  this->setDir (Tuple (1,0));
  
}

//------------------------------------------------------------------------------

void PowerUp::draw (void) {

  mvaddch (this->getPos (false),this->getPos (true),'?');
  
}

//------------------------------------------------------------------------------

void PowerUp::shift (void) {

  if (this->getPos (false) > 20)
    this->updatePos ();
  
}

//------------------------------------------------------------------------------

Projectile* PowerUp::randMissile (void) const {

  double ran = (double)rand ()/RAND_MAX * (96.875);
  Projectile* tmp;
  Tuple dir (-1,0);
  Tuple pos (-1,0);

  if (93.75 < ran)
    tmp = new FloodShot (pos,dir);
  else if (87.5 < ran && ran <= 93.75)
    tmp = new TriShot (pos,dir);
  else if (75.0 < ran && ran <= 87.5)
    tmp = new BombShot (pos,dir);
  else if (50 < ran && ran <= 75)
    tmp = new SliceShot (pos,dir);
  else
    tmp = new StubShot (pos,dir);

  return tmp;
  
}
