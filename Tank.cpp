//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Tank.hpp"

Tank::Tank (void) : Agent (Tuple (20,30),3) {

  powerTimer = 1;
  powerRefreshRate = 1;
  powerEnabled = false;
  proj = NULL;
  beenHit = false;
  hitTimer = 1;
  
}

//------------------------------------------------------------------------------

Tank::~Tank (void) {

  if (proj != NULL)
    delete proj;
  
}

//------------------------------------------------------------------------------

void Tank::setProj (Projectile* pow) {

  int id = pow->getIndex ();
  
  if (id == 12)
    powerRefreshRate = 1;
  else if (id == 11)
    powerRefreshRate = 3;
  else if (id == 10)
    powerRefreshRate = 4;
  else if (id == 8)
    powerRefreshRate = 2;
  else
    powerRefreshRate = 5;

  proj = pow;
  
}

//------------------------------------------------------------------------------

void Tank::flipPowerState (void) {

  powerEnabled = !powerEnabled;
  
}

//------------------------------------------------------------------------------

bool Tank::getPowerState (void) const {

  return powerEnabled;
  
}

//------------------------------------------------------------------------------

void Tank::updatePowerTimer (void) {

  powerTimer = (powerTimer+1) % powerRefreshRate;
  
}

//------------------------------------------------------------------------------

void Tank::canRevertState (void) {

  if (powerTimer) {
    this->updatePowerTimer ();
    return;
  }
  
  powerEnabled = false;
  delete proj;
  proj = NULL;
  
}

//------------------------------------------------------------------------------

void Tank::draw (void) {

  if (beenHit) {
    this->updateTimer ();
    return;
  }

  char tmp[6]={'/','*','A','*','\\'};

  int posY = this->getPos (false);
  int posX = this->getPos (true);

  attron (COLOR_PAIR (1));
  mvaddch (posY,posX,tmp[0]);
  mvaddch (posY,posX+4,tmp[4]);
  attroff (COLOR_PAIR (1));
      
  attron (A_BOLD);
  mvaddch (posY,posX+1,tmp[1]);
  mvaddch (posY,posX+3,tmp[3]);
  attroff (A_BOLD);
      
  attron (COLOR_PAIR (3));
  mvaddch (posY,posX+2,tmp[2]);
  attroff (COLOR_PAIR (3));
  
}

//------------------------------------------------------------------------------

bool Tank::hit (const Tuple& tup) const {

  if (tup.getL () != this->getPos (false))
    return false;

  for (int a (0);a<5;a++)
    if (tup.getR () == this->getPos (true)+a)
      return true;

  return false;
  
}

//------------------------------------------------------------------------------

bool Tank::hit (Tuple* tup) const {

  return this->hit (*tup);
  
}

//------------------------------------------------------------------------------

void Tank::flipHitState (void) {

  beenHit = !beenHit;
  
}

//------------------------------------------------------------------------------

void Tank::reduceHealth (Projectile* proj) {

  beenHit = true;
  Agent::reduceHealth (proj);

}

//------------------------------------------------------------------------------

void Tank::updateTimer (void) {

  if (beenHit)
    hitTimer = (hitTimer + 1) % 5;
  if (hitTimer)
    this->flipHitState ();
  
}

//------------------------------------------------------------------------------

Projectile* Tank::getPowerProjectile (void) const {

  return proj;
  
}
