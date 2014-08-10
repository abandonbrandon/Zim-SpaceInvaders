/*
Class : ShieldBlock
Description : represents an entire shield structure
Instances : 4
Hierarchical Level : 1
Functions :
|-> ShieldBlock Constructor : returns-> void; parameters-> int baseX, int baseY
*/

#ifndef SHIELDBLOCK_HPP_
#define SHIELDBLOCK_HPP_

#include "Tuple.hpp"
#include "Shield.hpp"

/* The ShieldBlock class is a group of Shield Objects.
 * It is one of the four blocks that exist in the game.
 * It handles collision of each separate shield object.
 */

class ShieldBlock {

public:

  ShieldBlock (Tuple*);
  ShieldBlock (Tuple);
  ~ShieldBlock (void);
  void draw (void) const;
  int getShields (void) const;
  bool collision (Tuple*);
  bool collision (const Tuple&);
  bool inVicinity (const Tuple&) const;
  bool inVicinity (Tuple*) const;

private:

  Tuple* Pos;
  Shield** shields;
  int lenShields;

  void setHit (int num);
  void removeDead (void);

};

#endif
