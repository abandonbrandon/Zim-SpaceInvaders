#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include "Tuple.hpp"
#include "Object.hpp"

/* The class Moveable is a child of the Object class.
 * It has attributes to everything that can move
 * as well as their directions. Some examples would
 * be the aliens and the Tank.
 */

class Movable : public Object {

public:

  Movable (Tuple*);
  ~Movable (void);
  Tuple nextPos (void) const;
  Tuple getDir (void) const;
  int getDir (bool) const;
  void setDir (Tuple*);
  void setDir (Tuple);
  bool getFlip (void) const;
  void updatePos (void);

private:

  Tuple* direction;
  bool flip;

  void flipSwitch (void);

};

#endif
