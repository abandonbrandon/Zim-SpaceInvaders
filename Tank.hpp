#ifndef TANK_HPP_
#define TANK_HPP_

#include "PowerUp.hpp"
#include "Projectile.hpp"
#include "Agent.hpp"

/* The Tank class is a child of the Agent Class.
 * It is the what the user gets to control. It is
 * the protector of humanity and when it dies, you
 * lose and have doomed the whole world/universe.
 */

class Tank : public Agent {

public:

  Tank (void);
  ~Tank (void);
  void setProj (Projectile*);
  Projectile* getPowerProjectile (void) const;
  void flipPowerState (void);
  
  bool getPowerState (void) const;
  void canRevertState (void);
  void draw (void);
  bool hit (const Tuple&) const;
  bool hit (Tuple*) const;
  void reduceHealth (Projectile*);
  
private:
  
  Projectile* proj;
  bool powerEnabled;
  int powerTimer;
  int powerRefreshRate;
  bool beenHit;
  int hitTimer;

  void updatePowerTimer (void);
  void flipHitState (void);
  void updateTimer (void);

};

#endif
