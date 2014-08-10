//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

//User Classes
#include "Agent.hpp"

Agent::Agent (Tuple* pos, int maxHP) : Movable (pos), hitPoints (maxHP) {
  
  dead = false;
  
} 

//------------------------------------------------------------------------------

Agent::Agent (Tuple pos, int maxHP) : Movable (&pos), hitPoints (maxHP) {

  dead = false;
  
}

//------------------------------------------------------------------------------

Agent::Agent (Tuple* pos) : Movable (pos) {

  dead = false;
  
}

//------------------------------------------------------------------------------

int Agent::getHP (void) const {

  return hitPoints;
  
}

//------------------------------------------------------------------------------

void Agent::death (void) {

  dead = true;
  
}

//------------------------------------------------------------------------------

void Agent::setHP (int num) {

  hitPoints = num;

  if (!num)
    this->death ();
}

//------------------------------------------------------------------------------

void Agent::reduceHealth (Projectile* pro) {

  this->setHP (hitPoints - pro->getDmg ());

  if (hitPoints <= 0)
    this->death ();
  
}

//------------------------------------------------------------------------------

bool Agent::hazDead (void) const {

  return dead;
  
}
