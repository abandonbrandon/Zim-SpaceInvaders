//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
using namespace std;

//User Classes
#include "Movable.hpp"

Movable::Movable (Tuple* pos) : Object (pos) {

  direction = NULL;
  flip = false;
  
}

//------------------------------------------------------------------------------

Movable::~Movable (void) {

  if (direction != NULL)
    delete direction;  
  
}

//------------------------------------------------------------------------------

Tuple Movable::nextPos (void) const {

  return this->getPos () + *direction;
  
}

//------------------------------------------------------------------------------

Tuple Movable::getDir (void) const {

  return Tuple (direction->getL (),direction->getR ());
  
}

//------------------------------------------------------------------------------

int Movable::getDir (bool flag) const {

  if (flag)
    return direction->getR ();
  else
    return direction->getL ();
  
}

//------------------------------------------------------------------------------

void Movable::setDir (Tuple* spe) {

  delete direction;
  direction = new Tuple (spe->getL (),spe->getR ());
  
}

//------------------------------------------------------------------------------

void Movable::setDir (Tuple dir) {

  this->setDir (&dir);
  
}

//------------------------------------------------------------------------------

void Movable::flipSwitch (void) {

  flip = !flip;
  
}

//------------------------------------------------------------------------------

bool Movable::getFlip (void) const {

  return flip;
  
}

//------------------------------------------------------------------------------

void Movable::updatePos (void) {

  this->setPos (this->nextPos ());

  this->flipSwitch ();

}
