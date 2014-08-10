#ifndef AGENT_HPP_
#define AGENT_HPP_

#include "Movable.hpp"
#include "Projectile.hpp"

/* The Agent class is a child of the Movable class.
 * It is the parent class of everything that has
 * hp as well as everything that can die. Examples
 * of an Agent would be the aliens.
 */

class Agent : public Movable  {

public:

  Agent (Tuple*,int);
  Agent (Tuple,int);
  Agent (Tuple*);
  int getHP (void) const;
  void setHP (int);
  void reduceHealth (Projectile*);
  void death (void);
  bool hazDead (void) const;

private:

  int hitPoints;
  bool dead;

};

#endif
