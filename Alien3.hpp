#ifndef ALIEN3_HPP_
#define ALIEN3_HPP_

#include "Alien.hpp"

/* A child of the Alien Class.
 * represents the strongest of 
 * the 3 aliens.
 */

class Alien3 : public Alien {

public:

  Alien3 (Tuple*);
  Alien3 (Tuple);
  void draw (void);
  void reduceHealth (Projectile*);

private:

  bool beenHit;
  int hitTimer;

  void flipHitState (void);
  void updateTimer (void);

};

#endif
