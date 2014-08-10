#ifndef STUBSHOT_HPP_
#define STUBSHOT_HPP_

#include "Projectile.hpp"

/* The StubShot is represented with a plus sign.
 * It is a shot that has hp itself and will die
 * only when it loses all its health or reaches
 * the screen. 
 */

class StubShot : public Projectile {

public:

  StubShot (Tuple*,Tuple*);
  StubShot (Tuple,Tuple);
  void draw (void) const;

};

#endif
