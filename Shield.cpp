//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Object.hpp"
#include "Tuple.hpp"
#include "List.hpp"
#include "Shield.hpp"

Shield::Shield (Tuple* pos) : Object (pos) {

  hit = false;

}

//------------------------------------------------------------------------------

bool Shield::getHit (void) const {

  return hit;
  
}

//------------------------------------------------------------------------------

void Shield::dead (void) {

  hit = true;
  
}

//------------------------------------------------------------------------------

void Shield::draw (void) const {

  char tmp='#';
  mvaddch (this->getPos (false),this->getPos (true),tmp | COLOR_PAIR (5));
  
}
