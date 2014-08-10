//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Projectile.hpp"

Projectile::Projectile (Tuple* pos, Tuple* dir) : Movable (pos) {

  this->setDir (dir);

}

//------------------------------------------------------------------------------

Projectile::Projectile (Tuple pos, Tuple dir) : Movable (&pos) {

  this->setDir (dir);
  
}

//------------------------------------------------------------------------------

void Projectile::draw (void) const {
}

//------------------------------------------------------------------------------

int Projectile::getDmg (void) const {

  return damage;
  
}

//------------------------------------------------------------------------------

void Projectile::setDmg (int num) {

  damage = num;
  
}

//------------------------------------------------------------------------------

void Projectile::operator=(const Projectile& proj) {

  Tuple tup_tmp;
  
  tup_tmp = proj.getPos ();
  this->setPos (tup_tmp);
  
  tup_tmp = proj.getDir ();
  this->setDir (tup_tmp);
  
  this->setDmg (proj.getDmg ());

}

//------------------------------------------------------------------------------

void Projectile::setIndex (int num) {
  
  index = num;
  
}

//------------------------------------------------------------------------------

int Projectile::getIndex (void) const {

  return index;
  
}
