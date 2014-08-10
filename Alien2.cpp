//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Alien2.hpp"

Alien2::Alien2 (Tuple* pos) : Alien (pos,50,75,60) {

  hitTimer = 1;
  beenHit = false;
  this->setHP (2);
  
}

//------------------------------------------------------------------------------

Alien2::Alien2 (Tuple pos) : Alien (pos,50,75,10) {

  hitTimer = 1;
  beenHit = false;
  this->setHP (2);

}

//------------------------------------------------------------------------------

void Alien2::flipHitState (void) {

  beenHit = !beenHit;
  
}

//------------------------------------------------------------------------------

void Alien2::reduceHealth (Projectile* proj) {

  beenHit = true;
  Agent::reduceHealth (proj);

}

//------------------------------------------------------------------------------

void Alien2::updateTimer (void) {

  hitTimer = (hitTimer + 1) % 5;
  
}

//------------------------------------------------------------------------------

void Alien2::draw (void) {

  if (beenHit) {
    if (!hitTimer)
      this->flipHitState ();
  
    else {
      this->updateTimer ();
      
      if (!(hitTimer%2)) {
        mvaddch (this->getPos (false),this->getPos (true),'o' | A_BOLD);
        mvaddch (this->getPos (false),this->getPos (true)+1,'^');
        mvaddch (this->getPos (false),this->getPos (true)+2,'o' | A_BOLD);
        
      }
      else
        return;
    }
  }

  if (this->getFlip ()) {
    mvaddch (this->getPos (false),this->getPos (true),'o' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+1,'^');
    mvaddch (this->getPos (false),this->getPos (true)+2,'o' | A_BOLD);
  }
  
  else {
    mvaddch (this->getPos (false),this->getPos (true),'*' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+1,'^');
    mvaddch (this->getPos (false),this->getPos (true)+2,'*' | A_BOLD);
  }

}
