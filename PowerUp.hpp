#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "Movable.hpp"
#include "Projectile.hpp"

/* The PowerUp class is a child of Movable.
 * The PowerUp class has a random generater
 * that will handle what powerUp is spawned.
 */

class PowerUp : public Movable {

public:

  PowerUp (Tuple*);
  PowerUp (Tuple);
  Projectile* randMissile (void) const;
  void draw (void);
  void shift (void);

};

#endif
