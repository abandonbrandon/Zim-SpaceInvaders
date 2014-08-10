#ifndef REGSHOT_HPP_
#define REGSHOT_HPP_

#include "Projectile.hpp"

/* The RegShot class is a child of the Projectile class.
 * It is the default shot for both the aliens and the tank.
 */

class RegShot : public Projectile {

public:

  RegShot (Tuple*,Tuple*);
  RegShot (Tuple,Tuple);
  void draw (void) const;

};

#endif
