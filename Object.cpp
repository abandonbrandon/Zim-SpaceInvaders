//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Object.hpp"
#include "Tuple.hpp"

Object::Object (Tuple* pos) {

  Pos = new Tuple (pos->getL (),pos->getR ());
  
}

//------------------------------------------------------------------------------

Object::~Object (void) {

  delete Pos;
  
}

//------------------------------------------------------------------------------

int Object::getPos (bool flag) const {

  if (flag)
    return Pos->getR ();
  else
    return Pos->getL ();
  
}

//------------------------------------------------------------------------------

Tuple Object::getPos (void) const {

  return Tuple (Pos->getL (), Pos->getR ());
  
}

//------------------------------------------------------------------------------

void Object::setPos (Tuple tup) {

  this->setPos (&tup);
  
}

//------------------------------------------------------------------------------

void Object::setPos (Tuple* pos) {

  if (*pos == *Pos)
    return;

  delete Pos;
  Pos = new Tuple (pos->getL (),pos->getR ());
  
}

//------------------------------------------------------------------------------

void Object::resetCursor (void) const {

  move (0,0);
  
}
