/*
Class : Shield
Description : represents the basic unit comprising the shield blocks
Instances : 76
Hierarchical Level : 2
Functions :
|-> Shield Constructor : returns-> void
Variables :
|-> hit : has actor been hit
*/

#ifndef SHIELD_HPP_
#define SHIELD_HPP_

#include "Object.hpp"

/* The shield class is each individual shield of
 * each block. It handles when it dies and what
 * it will block a shot.
 */

class Shield : public Object {

public:
  
  Shield (Tuple*);
  bool getHit (void) const;
  void dead (void);
  void draw (void) const;

private:

  bool hit;
  
};

#endif
