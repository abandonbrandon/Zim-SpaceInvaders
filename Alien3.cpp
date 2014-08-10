//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Alien3.hpp"

Alien3::Alien3 (Tuple* pos) : Alien (pos,75,100,30) {

  hitTimer = 1;
  beenHit = false;
  this->setHP (3);
  
}

//------------------------------------------------------------------------------

Alien3::Alien3 (Tuple pos) : Alien (pos,75,100,5) {

  hitTimer = 1;
  beenHit = false;
  this->setHP (3);

}

//------------------------------------------------------------------------------

void Alien3::flipHitState (void) {

  beenHit = !beenHit;
  
}

//------------------------------------------------------------------------------

void Alien3::reduceHealth (Projectile* proj) {

  beenHit = true;
  Agent::reduceHealth (proj);

}

//------------------------------------------------------------------------------

void Alien3::updateTimer (void) {

  hitTimer = (hitTimer + 1) % 5;
  
}

//------------------------------------------------------------------------------

void Alien3::draw (void) {

  if (beenHit) {
    if (!hitTimer)
      this->flipHitState ();
  
    else {
      this->updateTimer ();
      
      if (!(hitTimer%2)) {
        mvaddch (this->getPos (false),this->getPos (true),'/' | A_BOLD);
        mvaddch (this->getPos (false),this->getPos (true)+2,'\\' | A_BOLD);
        mvaddch (this->getPos (false),this->getPos (true)+1,'-');
      }
      else
        return;
    }
  }

  if (this->getFlip ()) {
    mvaddch (this->getPos (false),this->getPos (true),'/' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+2,'\\' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+1,'-');
  }
  
  else {
    mvaddch (this->getPos (false),this->getPos (true),'\\' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+2,'/' | A_BOLD);
    mvaddch (this->getPos (false),this->getPos (true)+1,'_');
  }

}
