#ifndef BOMBSHOT_HPP_
#define BOMBSHOT_HPP_

#include "Projectile.hpp"
#include "List.hpp"

/* The BombShot class is a child of Projectile.
 * It is a limited shot that deals damage in a
 * 11x1 area after coming in contact with an alien.
 * The center of the area is where the alien comes
 * into contact with the bombshot.
 */
 
class BombShot : public Projectile {

public:

  BombShot (Tuple*,Tuple*);
  BombShot (Tuple,Tuple);
  void draw (void) const;
  void DmgArea (List*&) const;

};

#endif
