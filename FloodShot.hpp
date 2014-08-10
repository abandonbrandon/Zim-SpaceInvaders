#ifndef FLOODSHOT_HPP_
#define FLOODSHOT_HPP_

#include "Projectile.hpp"

/* The Floodshot is a child of the Projectile class.
 * It is called on by the PowerUp class. When it is
 * shot, it will shoot the screen width with the
 * length of 1.
 */ 

class FloodShot : public Projectile {

public:

  FloodShot (Tuple*,Tuple*);
  FloodShot (Tuple,Tuple);
  void draw (void) const;

};

#endif
