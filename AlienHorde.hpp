#ifndef ALIENHORDE_HPP_
#define ALIENHORDE_HPP_

#include "Alien1.hpp"
#include "Alien2.hpp"
#include "Alien3.hpp"
#include "List.hpp"

/* The Aliene Horde class is a class
 * that handles all the aliens and all
 * their collisions as well as when they
 * can shoot. It also controls the whole
 * group and how they move.
 */

class AlienHorde {

public:

  AlienHorde (Tuple);
  ~AlienHorde (void);
  bool touchDown (void) const;
  
  bool collision (const Tuple&,Projectile*,int&);
  bool collision (Tuple*,Projectile*,int&);
  void draw (void) const;
  
  bool updatePos (void);
  bool inVicinity (const Tuple&) const;
  bool inVicinity (Tuple*) const;
  
  void fire (int,int&,int*&,List*&) const;
  void powerCatalog (bool*&) const;
  int getDir (void) const;
  int getLen (void) const;
  
  bool hitConst (const Tuple&) const;
  Tuple posbyID (int) const;
  void getArea (int,List*&) const;

private:

  Tuple* Pos;
  Tuple* topLeft;
  Tuple* botRight;
  int dir;
  bool hasShifted;
  
  Alien1** alien1;
  Alien2** alien2;
  Alien3** alien3;
  
  int len1;
  int len2;
  int len3;
  int len;
  
  bool allDead1;
  bool allDead2;
  bool allDead3;
  bool allDead;

  int* deadlings;
  List* posOfDead;
  int lenDead;

//------------------------

  void setCorners (void);
  void setTL (void);
  void setBR (void);
  
  void removeDead1 (void);
  void removeDead2 (int&);
  void removeDead3 (int&);
  
  void draw1 (void) const;
  void draw2 (void) const;
  void draw3 (void) const;
  
  bool collision1 (const Tuple&,int&);
  bool collision2 (const Tuple&,Projectile*,int&);
  bool collision3 (const Tuple&,Projectile*,int&);
  
  bool touchDown1 (void) const;
  bool touchDown2 (void) const;
  bool touchDown3 (void) const;

  void shift (void);
  void shift1 (void);
  void shift2 (void);
  void shift3 (void);
  
  void move (void);
  void move1 (void);
  void move2 (void);
  void move3 (void);

  bool inVicinity1 (const Tuple&) const;
  bool inVicinity2 (const Tuple&) const;
  bool inVicinity3 (const Tuple&) const;

  void fire1 (int,int&,int*&,List*&) const;
  void fire2 (int,int&,int*&,List*&) const;
  void fire3 (int,int&,int*&,List*&) const;

  bool hitConst1 (const Tuple&) const;
  bool hitConst2 (const Tuple&) const;
  bool hitConst3 (const Tuple&) const;

  Tuple posbyID1 (int) const;
  Tuple posbyID2 (int) const;
  Tuple posbyID3 (int) const;

  
  
};

#endif
