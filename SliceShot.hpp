#ifndef SLICESHOT_HPP_
#define SLICESHOT_HPP_

#include "Projectile.hpp"

/* The SliceShot is represented with a dollar sign.
 * It pierces everything that gets in it way. It will
 * keep traveling til it reaches the end of the screen.
 */

class SliceShot : public Projectile {

public:

  SliceShot (Tuple*,Tuple*);
  SliceShot (Tuple,Tuple);
  void draw (void) const;

};

#endif
