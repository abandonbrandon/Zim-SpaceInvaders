#ifndef TRISHOT_HPP_
#define TRISHOT_HPP_

#include "Projectile.hpp"

/* The TriShot is a shot that shoots 3 regular shots
 * side by side. It can kill at most 2 aliens. This
 * PowerUp is the most often powerUp spawned. 
 */

class TriShot : public Projectile {

public:

  TriShot (Tuple*,Tuple*);
  TriShot (Tuple,Tuple);
  void draw (void) const;

};

#endif
