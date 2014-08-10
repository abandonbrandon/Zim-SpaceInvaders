//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Alien1.hpp"

Alien1::Alien1 (Tuple* pos) : Alien (pos,25,50,120) {

  this->setHP (1);
  
}

//------------------------------------------------------------------------------

Alien1::Alien1 (Tuple pos) : Alien (pos,25,50,20) {

  this->setHP (1);

}

//------------------------------------------------------------------------------

void Alien1::draw (void) const {

  if (this->getFlip ()) {
    mvaddch (this->getPos (false),this->getPos (true),'_' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+2,'_' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+1,'x');
  }
  
  else {
    mvaddch (this->getPos (false),this->getPos (true),'-' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+2,'-' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+1,'x');
  }

}
