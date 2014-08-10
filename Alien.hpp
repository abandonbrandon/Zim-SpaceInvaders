#ifndef ALIEN_HPP_
#define ALIEN_HPP_

#include "Enemy.hpp"
#include "PowerUp.hpp"

/* The Alien class is a child of the Enemy class.
 * This class controls aliens individually as to
 * check when they have shot and when they will 
 * drop a PowerUp.
 */

class Alien : public Enemy {

public:

  Alien (Tuple*,int,int,int);
  Alien (Tuple,int,int,int);
  void shift (void);
  int getInt (void) const;
  bool canHazFire (int);
  bool getPowerState (void) const;
  bool hasTouchedDown (void) const;
  bool hit (const Tuple&) const;
  bool hit (Tuple*) const;
  int getID (void) const;
  void setID (int);

private:

  int probSpawn;
  bool touchdown;
  int probFire;
  bool hasPower;
  int ID;
  bool hasFired;
  int hitTimer;
  int hitRefreshRate;

  void canHazPower (void);
  void updateTimer (void);
  
};

#endif
