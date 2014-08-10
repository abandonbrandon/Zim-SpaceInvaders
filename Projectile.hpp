#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "Movable.hpp"

/* The Projectile class is a child of the Movable class
 * It is any projectile such as alien's shot or the tank's
 * shot. It moves at a different speed than Agents.
 */

class Projectile : public Movable {

public:

  Projectile (Tuple*,Tuple*);
  Projectile (Tuple,Tuple);
  int getDmg (void) const;
  void setDmg (int);
  virtual void draw (void) const;
  void operator=(const Projectile&);
  void setIndex (int);
  int getIndex (void) const;

private:

  int damage;
  int index;

};

#endif
