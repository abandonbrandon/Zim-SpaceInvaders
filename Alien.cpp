//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
using namespace std;

//User Classes
#include "Alien.hpp"
#include "PowerUp.hpp"
#define D(x) ((x==1)?-1:1)

Alien::Alien (Tuple* pos, int probS, int probF, int shotDelay) : Enemy (pos) {

  this->setDir (Tuple (0,1));
  
  touchdown = false;

  probSpawn = probS;  
  this->canHazPower ();
  probFire = probF;
  hasFired = false;
  hitTimer = 1;
  hitRefreshRate = shotDelay;

}

//------------------------------------------------------------------------------

Alien::Alien (Tuple pos, int probS, int probF, int shotDelay) : Enemy (&pos) {

  this->setDir (Tuple (0,1));
  
  touchdown = false;

  probSpawn = probS;
  this->canHazPower ();
  probFire = probF;
  
  hasFired = false;
  hitTimer = 1;
  hitRefreshRate = shotDelay;

}

//------------------------------------------------------------------------------

void Alien::shift (void) {

  if (this->getPos (false) >= 20)
    touchdown = true;
  else {
    this->setPos (Tuple (this->getPos (false)+1,this->getPos (true)));
    this->setDir (Tuple (0,D(this->getDir ().getR ())));
  }

}

//------------------------------------------------------------------------------

bool Alien::canHazFire (int num) {

  this->updateTimer ();

  if (hitTimer)
    return false;
  
  int bar = probFire / pow (2,abs (this->getPos (true)+ 1 - num));
  int ran = this->getInt ();
  hasFired = (ran <= bar);

  return hasFired;

}

//------------------------------------------------------------------------------

int Alien::getInt (void) const {

  return (rand () % 100) + 1;
  
}

//------------------------------------------------------------------------------

void Alien::canHazPower (void) {

  hasPower = (this->getInt () <= probSpawn);

}

//------------------------------------------------------------------------------

bool Alien::hasTouchedDown (void) const {

  return touchdown;
  
}

//------------------------------------------------------------------------------

bool Alien::getPowerState (void) const {

  return hasPower;
  
}

//------------------------------------------------------------------------------

bool Alien::hit (const Tuple &tup) const {

  if (tup.getL () != this->getPos (false))
    return false;

  int xmax = this->getPos (true)+2;
  int xmin = this->getPos (true);

  return (tup.getR () <= xmax && tup.getR () >= xmin);
  
}

//------------------------------------------------------------------------------

bool Alien::hit (Tuple* pt) const {

  return this->hit (*pt);
  
}

//------------------------------------------------------------------------------

int Alien::getID (void) const {

  return ID;
  
}

//------------------------------------------------------------------------------

void Alien::setID (int num) {

  ID = num;
  
}

//------------------------------------------------------------------------------

void Alien::updateTimer (void) {

  if (!hitTimer)
    hasFired = false;
      
  hitTimer = (hitTimer + 1) % hitRefreshRate;
  
}
