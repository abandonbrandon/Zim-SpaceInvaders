#ifndef GAME_HPP_
#define GAME_HPP_

#include "ShieldBlock.hpp"
#include "AlienHorde.hpp"
#include "Projectile.hpp"
#include "PowerUp.hpp"
#include "Tank.hpp"
#include "AlienHorde.hpp"
#include "AlienHorde.hpp"
#include "RegShot.hpp"

class Game {

public:

  Game (void);
  ~Game (void);
  void drawActor (void);
  bool endGame (void) const;
  int reasonEndGame (void) const;
  void getInput (void);
  void moveActors (void);
  void fire (void);
  void collision (void);
  void calculate (void);
  
private:

  ShieldBlock** shield;
  AlienHorde* alien;
  
  RegShot** hostile;
  int *idx;
  
  int* powerID;
  bool* powerFilter;

  int alienTimer;
  int alienRefreshRate;
  int alienFireTimer;

  Projectile** friendly;
  
  int projTimer;

  PowerUp* power;
  Tank* player;

  bool powerCanSpawn;
  bool drawPower;

  int powerTimer;
  
  bool pressedQ;
  bool shieldBlock[4];
  int score;

//---------------------------  
  
  void clearProj (void);
  void alienMissileClear (void);
  void playerMissileClear (void);
  
  void stubHandle (int);
  void singleSpecialMisHandle (bool);
  void singleMissileHandle (void);
  void bombCollide (void);
  void collide (void);
  
  void alienOnTarget (void);
  void alienMissileCollide (void);
  void playerMissileCollide (void);
  
  void powerCollide (void);
  void powerReset (void);
  void updateTimer (int&,int) const;
  void idle (void) const;
  void fillDeath (int);

  void moveAlien (void);
  void moveProj (void);

  void setPower (Projectile*,int);
  void setTriShot (void);
  void setStubShot (int);
  void setFloodShot ();
  void setSliceShot (int);
  void setBombShot (int);

  void startUp (void) const;
  void shieldSetup (void);
  void setInitConditions (void);
  void setHostiles (void);
  void powerInit (void);
  void friendInit (void);

  void alienFire (void);

};

#endif
