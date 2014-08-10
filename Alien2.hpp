#ifndef ALIEN2_HPP_
#define ALIEN2_HPP_

#include "Alien.hpp"

/* A child of the Alien Class.
 * represents the middle of 
 * the 3 aliens.
 */

class Alien2 : public Alien {

public:

  Alien2 (Tuple*);
  Alien2 (Tuple);
  void draw (void);
  void reduceHealth (Projectile*);

private:

  bool beenHit;
  int hitTimer;

  void flipHitState (void);
  void updateTimer (void);

};

#endif
