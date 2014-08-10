#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "Agent.hpp"

/* The Enemy class is a child of the Agent class
 * This class is the class that controls all the 
 * enemies such as the aliens and their 
 * attributes.
 */

class Enemy : public Agent  {

public:

  Enemy (Tuple*,int);
  Enemy (Tuple,int);
  Enemy (Tuple*);
  int getScore (void) const;
  void setScore (int);

private:

int score;

};

#endif
