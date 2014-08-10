/*
Class : Object
Description : represents the template from which other objects will derive their basic properties
Instances : 0
Hierarchical Level : 1
Functions :
        Object Constructor : parameters-> const Tuple*& position
        ~Object destructor
Variables :
*/

/* The Object class is anything that has a position.
 * It is the father/mother of every object in the game
 * as everything in our game has a position. Text are 
 * not included as an object.
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "Tuple.hpp"

class Object {

public:

  Object (Tuple*);
  ~Object (void);
  int getPos (bool) const;
  Tuple getPos (void) const;
  void setPos (Tuple*);
  void setPos (Tuple);
  void resetCursor (void) const;

private:
  
  Tuple* Pos;

};

#endif  
