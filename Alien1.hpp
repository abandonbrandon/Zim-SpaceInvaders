#ifndef ALIEN1_HPP_
#define ALIEN1_HPP_

#include "Alien.hpp"

/* A child of the Alien Class.
 * represents the weakest of 
 * the 3 aliens.
 */

class Alien1 : public Alien {

public:

  Alien1 (Tuple*);
  Alien1 (Tuple);
  void draw (void) const;
  
};

#endif
