//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <ctime>
#define HEIGHT 20
#define BASE HEIGHT*3
#define DELAY 1000

#include <iostream>
using namespace std;

//User Classes
#include "Game.hpp"
#include "ShieldBlock.hpp"
#include "AlienHorde.hpp"
#include "Projectile.hpp"
#include "PowerUp.hpp"
#include "Tank.hpp"
#include "AlienHorde.hpp"
#include "AlienHorde.hpp"
#include "RegShot.hpp"
#include "StubShot.hpp"
#include "FloodShot.hpp"
#include "SliceShot.hpp"
#include "TriShot.hpp"
#include "BombShot.hpp"
#define ACCEL 2

Game::Game (void) {
  
  this->startUp ();
  this->setInitConditions ();
  this->shieldSetup ();
  
  alien = new AlienHorde (Tuple (1,1));
  this->setHostiles ();

  this->powerInit ();

  this->friendInit ();
  

  power = new PowerUp (Tuple (0,0));
  player = new Tank;

  powerTimer = 1;
  projTimer = 1;
  
  alienTimer = 1;
  alienRefreshRate = 16;

}

//------------------------------------------------------------------------------

Game::~Game (void) {

  if (shield != NULL) {
    for (int a (0);a<4;a++)
      if (shield[a] != NULL)
        delete shield[a];

    delete[] shield;
  }

  if (alien != NULL)
    delete alien;

  if (hostile != NULL) {
    for (int b (0);b<40;b++)
      if (hostile[b] != NULL)
        delete hostile[b];

    delete[] hostile;
  }


  if (friendly != NULL) {
    for (int c (0);c<60;c++)
      if (friendly[c] != NULL)
        delete friendly[c];
    
    delete[] friendly;
  }
  
  delete power;
  delete player;
  
}

//------------------------------------------------------------------------------

void Game::startUp (void) const {

  srand (time (NULL));
  clear ();
  initscr ();  //Initializes screen for usage
  noecho (); //do not print out characters from input stream
  cbreak (); // forego buffer completely
  start_color (); // initiate color

  init_pair (1,COLOR_BLUE,COLOR_BLACK);
  init_pair (2,COLOR_GREEN,COLOR_BLACK);
  init_pair (3,COLOR_RED,COLOR_BLACK);
  init_pair (4,COLOR_CYAN,COLOR_BLACK);
  init_pair (5,COLOR_YELLOW,COLOR_BLACK);
  init_pair (6,COLOR_MAGENTA,COLOR_BLACK);
}

//------------------------------------------------------------------------------

void Game::shieldSetup (void) {

  shield = new ShieldBlock*[4];
  for (int a (0);a<4;a++)
    shield[a] = new ShieldBlock (Tuple (15,8+13*a));

  for (int b (0);b<4;b++)
    shieldBlock[b] = true;
  
}

//------------------------------------------------------------------------------

void Game::setInitConditions (void) {

  pressedQ = false;

  drawPower = false;
  powerCanSpawn = true;
  
}

//------------------------------------------------------------------------------

void Game::setHostiles (void) {

  hostile = new RegShot*[40];
  for (int a (0);a<40;a++)
    hostile[a] = NULL;
  
}

//------------------------------------------------------------------------------

void Game::powerInit (void) {

  alien->powerCatalog (powerFilter);

}

//------------------------------------------------------------------------------

void Game::friendInit (void) {

  friendly = new Projectile*[60];

  for (int a (0);a<60;a++)
    friendly[a] = NULL;
  
}

//------------------------------------------------------------------------------

void Game::drawActor (void) {

  attron (COLOR_PAIR (6));

  for (int a (0);a<40;a++)
    if (hostile[a] != NULL) {
      hostile[a]->draw ();
    }
  
  attroff (COLOR_PAIR (6));

  attron (COLOR_PAIR (4));

  if (friendly != NULL)
    for (int b (0);b<60;b++) {
      if (friendly[b] != NULL)
        friendly[b]->draw ();
    }

  attroff (COLOR_PAIR (4));
  
  if (drawPower)
    power->draw ();

  for (int c (0);c<4;c++)
    if (!shieldBlock[c])
      continue;
    else
      shield[c]->draw ();

  if (alien != NULL)
    alien->draw ();
  
  if (!player->getPowerState ())
    powerCanSpawn = true;
  player->draw ();

  move (0,0);
  
}

//------------------------------------------------------------------------------

bool Game::endGame (void) const {

  return pressedQ || player->hazDead () || !alien->getLen () || alien->touchDown ();
  
}

//------------------------------------------------------------------------------

void Game::getInput (void) {

  int moveTank (0);
  bool isMove (false);
  int disp (0);
  int ran = rand()%99;

  char ch = 'i';
  ch = getch ();

  if (ch == 'a') {
    moveTank = -2;
    isMove = true;
  }

  else if (ch == 'd') {
    moveTank = 2;
    isMove = true;
  }

  else if (ch == 'j') {
    disp = 1;
    isMove = false;
  }

  else if (ch == 'k') {
    disp = 2;
    isMove = false;
  }

  else if (ch == 'l') {
    disp = 3;
    isMove = false;
  }

  else if (ch == 'q') {
    pressedQ = true;
    return;
  }

  else if (ch == 'p') {
    char canQuit='a';
    WINDOW* win = newwin (1,10,10,30);

    attron (A_BOLD);
    attron (A_UNDERLINE);
    mvwaddstr (win,0,0,"[ Paused ]");
    attroff (A_UNDERLINE);
    attroff (A_BOLD);
    move (0,0);

    wrefresh (win);
    
    do {
      canQuit = getch ();
      this->idle ();
    } while (canQuit != 'p' && canQuit != 'q');

    delwin (win);
    if (canQuit == 'q')
      pressedQ = true;
    return;
  }

  else
    return;


  if (isMove) {
    if ((moveTank == -2 && player->getPos (true) < 2) || (moveTank == 2 && player->getPos (true) > 58))
      return;
    player->setPos (Tuple (player->getPos (false),player->getPos (true)+moveTank));
  }
  else {

    for (int a (0);a<60;a++)
      if (friendly[a] != NULL)
        return;

    if (player->getPowerState ()) {
      if (player->getPowerProjectile () == NULL) {
        
        player->setProj (power->randMissile ());
        this->setPower (player->getPowerProjectile (),disp);
      }
      
      else {
        this->setPower (player->getPowerProjectile (),disp);
        player->canRevertState ();
      }
    }
    
    else {
      friendly[0] = new RegShot (Tuple (player->getPos (false)-1,player->getPos (true)+disp), Tuple (-1,0));
    }

  }
  
}

//------------------------------------------------------------------------------

void Game::setPower (Projectile* p, int disp) {

  switch (p->getIndex ()) {
        
  case 8:
    this->setTriShot ();
    return;
        
  case 9:
    this->setStubShot (disp);
    return;
        
  case 10:
    this->setSliceShot (disp);
    return;
        
  case 11:
    this->setBombShot (disp);
    return;
      
  case 12:
    this->setFloodShot ();
    return;
        
  }

}

//------------------------------------------------------------------------------

void Game::setTriShot (void) {

  int ypos = player->getPos (false)-1;
  int xpos = player->getPos (true)+1;
  for (int a (0);a<3;a++)
    friendly[a] = new TriShot (Tuple (ypos,xpos+a), Tuple (-1,0));
  
}

//------------------------------------------------------------------------------

void Game::setStubShot (int disp) {

  int ypos = player->getPos (false)-1;
  int xpos = player->getPos (true)+disp;
  friendly[0] = new StubShot (Tuple (ypos,xpos), Tuple (-1,0));
  
}

//------------------------------------------------------------------------------

void Game::setSliceShot (int disp) {

  int ypos = player->getPos (false)-1;
  int xpos = player->getPos (true)+disp;
  friendly[0] = new SliceShot (Tuple (ypos,xpos), Tuple (-1,0));
  
}

//------------------------------------------------------------------------------

void Game::setBombShot (int disp) {

  int ypos = player->getPos (false)-1;
  int xpos = player->getPos (true)+disp;
  friendly[0] = new BombShot (Tuple (ypos,xpos), Tuple (-1,0));
  
}

//------------------------------------------------------------------------------

void Game::setFloodShot (void) {

  int ypos = player->getPos (false)-1;
  for (int a (0);a<60;a++)
    friendly[a] = new FloodShot (Tuple (ypos,a), Tuple (-1,0));
    
}

//------------------------------------------------------------------------------

void Game::moveActors (void) {
  
  this->updateTimer (alienTimer,alienRefreshRate);
  this->updateTimer (projTimer,1);
  this->updateTimer (powerTimer,50);
  
  this->moveAlien ();
  this->moveProj ();
  
}

//------------------------------------------------------------------------------

void Game::moveAlien (void) {

  if (!alien->getLen () || alienTimer)
    return;
    
  if (!alien->updatePos () && alienRefreshRate > 2)
    alienRefreshRate /= 2;
    
}

//------------------------------------------------------------------------------

void Game::updateTimer (int& timer, int refreshRate) const {

  ++timer;
  timer %= refreshRate;
  
}

//------------------------------------------------------------------------------

void Game::moveProj (void) {

  if (projTimer)
    return;
  
  if (hostile != NULL)
    for (int b (0);b<40;b++)
      if (hostile[b] != NULL)
        hostile[b]->updatePos ();

  if (friendly != NULL)
    for (int c (0);c<60;c++)
      if (friendly[c] != NULL)
        friendly[c]->updatePos ();
  
}

//------------------------------------------------------------------------------

void Game::fire (void) {
  
  this->alienFire ();
  
}

//------------------------------------------------------------------------------

void Game::alienFire (void) {

  List* tmp;
  int length;
  int* idx;

  int counter (0);
  for (int a (0);a<40;a++)
    if (hostile[a] != NULL)
      ++counter;

  if (counter >= 3)
    return;
  
  alien->fire (player->getPos (true),length,idx,tmp);

  if (!length)
    return;
  
  int id = rand ()%length;
      
  if (hostile[idx[id]] == NULL)
    hostile[idx[id]] = new RegShot (tmp->getTup (id),Tuple (1,0));
  
  if (tmp != NULL)
    delete tmp;
  if (idx != NULL)  
    delete[] idx;
        
}

//------------------------------------------------------------------------------

void Game::clearProj (void) {

  this->alienMissileClear ();
  this->playerMissileClear ();
      
}

//------------------------------------------------------------------------------

void Game::playerMissileClear (void) {

  for (int a (0);a<60;a++)
    if (friendly[a] != NULL)
      if (friendly[a]->getPos (false) <= 0) {
        delete friendly[a];
        friendly[a] = NULL;
      }
  
}

//------------------------------------------------------------------------------

void Game::alienMissileClear (void) {

  for (int a (0);a<40;a++)
    if (hostile[a] != NULL)
      if (hostile[a]->getPos (false) >= 21) {
        delete hostile[a];
        hostile[a] = NULL;
      }
  
}

//------------------------------------------------------------------------------

void Game::collide (void) {

  this->powerCollide ();
  this->alienOnTarget ();
  this->alienMissileCollide ();
  this->playerMissileCollide ();

}


//------------------------------------------------------------------------------

void Game::stubHandle (int hp) {

  if (((Projectile*)friendly[0])->getDmg () <= 1) {
    delete friendly[0];
    friendly[0] = NULL;
      
  }
  else
    ((Projectile*)friendly[0])->setDmg (((Projectile*)friendly[0])->getDmg ()-hp);

}

//------------------------------------------------------------------------------

void Game::singleSpecialMisHandle (bool isStub) {

  int hp (0);

  if (alien->hitConst (friendly[0]->getPos ())) {
    int id;
    alien->collision (friendly[0]->getPos (),friendly[0],id);

    if (isStub) {
      if (id < 10)
        hp = 3;
      else if (id >=10 && id < 20)
        hp = 2;
      else
        hp = 1;
    }
  }
    
  for (int b (0);b<4;b++) {
    if (!shieldBlock[b])
      continue;
          
    if (shield[b]->collision (friendly[0]->getPos ())) {
      if (shield[b]->getShields () <= 0)
        shieldBlock[b] = false;
      hp = 1;
    }
        
  }

  if (isStub)
    this->stubHandle (hp);
  
}

//------------------------------------------------------------------------------

void Game::powerCollide (void) {

  if (!drawPower || player->getPowerState ())
    return;

  if (player->hit (power->getPos ())) {
    drawPower = false;
    powerTimer = 1;
    player->flipPowerState ();
    powerCanSpawn = false;
  }

  for (int a (0);a<60;a++)
    if (friendly[a] != NULL)
      if (power->getPos () == friendly[a]->getPos ()) {
        drawPower = false;
        player->flipPowerState ();
        powerCanSpawn = false;
        
        delete friendly[a];
        friendly[a] = NULL;
        break;
      }
  
}

//------------------------------------------------------------------------------

void Game::alienOnTarget (void) {

  List** tmp = new List*[40];

  for (int a (0);a<40;a++) {

    alien->getArea (a,tmp[a]);
  }

  for (int b (0);b<40;b++) {
    if (tmp[b] == NULL)
      continue;

    for (int c (0);c<3;c++)
      for (int d (0);d<4;d++) {
        
        if (!shieldBlock[d])
          continue;
        
        if (shield[d]->collision (tmp[b]->getTup (c)))
          if (shield[d]->getShields () <= 0)
            shieldBlock[d] = false;
      }
  }
  
  for (int q (0);q<40;q++) {
    if (tmp[q] == NULL)
      continue;
    
    for (int e (0);e<3;e++) {
      
      RegShot std (tmp[q]->getTup (e),Tuple (0,0));
      if (player->hit (std.getPos ()))
        player->reduceHealth (&std);
    }
  }

  for (int f (0);f<40;f++)
    if (tmp[f] != NULL) {
      delete tmp[f];
      tmp[f] = NULL;
    }

  delete[] tmp;
  
}

//------------------------------------------------------------------------------

void Game::alienMissileCollide (void) {

  for (int a(0);a<40;a++) {
    
    if (hostile[a] == NULL)
      continue;
    
    if (player->hit (hostile[a]->getPos ())) {
      player->reduceHealth (hostile[a]);
      delete hostile[a];
      hostile[a] = NULL;
    }
      
    else {
      for (int b (0);b<4;b++) {
        if (!shieldBlock[b])
          continue;

        if (hostile[a] != NULL && shield[b]->collision (hostile[a]->getPos ())) {
            
          if (shield[b]->getShields () <= 0)
            shieldBlock[b] = false;
          delete hostile[a];
          hostile[a] = NULL;

        }
      }
        
    }
  }

}

//------------------------------------------------------------------------------

void Game::playerMissileCollide (void) {

  if (player->hazDead ())
    return;

  bool isActive (false);
  int placement (-1);
  
  for (int id (0);id<60;id++)
    if (friendly[id] != NULL) {
      placement = id;
      isActive = true;
      break;
    }

  if (!isActive || placement == -1)
    return;
  
  int idx = friendly[placement]->getIndex ();
  
  if (idx == 11)
    this->bombCollide ();
  else if (idx == 9 || idx == 10)
    this->singleSpecialMisHandle (idx == 9);
  else
    this->singleMissileHandle ();
  
}

//------------------------------------------------------------------------------

void Game::calculate (void) {

  this->idle ();
  this->moveActors ();
  this->clearProj ();
  
  this->fire ();
  this->collide ();

  
}

//------------------------------------------------------------------------------

void Game::bombCollide (void) {

  Tuple tup = friendly[0]->getPos ();

  if (!(alien->hitConst (tup)  || shield[0]->collision (tup) || shield[1]->collision (tup) || shield[2]->collision (tup) || shield[3]->collision (tup)))
    return;
  
  RegShot std (Tuple (-1,-1), Tuple (0,0));

  List* area;

  ((BombShot*)friendly[0])->DmgArea (area);

  int length = area->elements ();
  
  for (int a(0);a<length;a++) {
      
    if (alien->hitConst (area->getTup (a))) {
      int id;
      alien->collision (area->getTup (a),&std,id);
      
    }
      
    for (int b (0);b<4;b++) {
      if (!shieldBlock[b])
        continue;
      if (shield[b]->collision (area->getTup (a))) {
        if (shield[b]->getShields () <= 0)
          shieldBlock[b] = false;
      }
    }

  }

  delete friendly[0];
  friendly[0] = NULL;
  
}

//---------------------------------------------------------------------------

void Game::singleMissileHandle (void) {

  RegShot std (Tuple (-1,-1), Tuple (-1,-1));

  for (int a (0);a<60;a++) {
    if (friendly[a] == NULL)
      continue;
    
    if (alien->hitConst (friendly[a]->getPos ())) {
      int id;
      alien->collision (friendly[a]->getPos (),&std,id);

      delete friendly[a];
      friendly[a] = NULL;
      
      if (powerFilter[id] && powerCanSpawn && !player->getPowerState () && id != -1 && !drawPower) {
        powerCanSpawn = false;
          
        drawPower = true;
        power->setPos (alien->posbyID (id));
      }
    }

    if (friendly[a] == NULL)
      continue;
    
    for (int b (0);b<4;b++) {
      if (!shieldBlock[b])
        continue;
      if (shield[b]->collision (friendly[a]->getPos ())) {
        if (shield[b]->getShields () <= 0)
          shieldBlock[b] = false;

        delete friendly[a];
        friendly[a] = NULL;
        break;
      }
    }
  }
}

//---------------------------------------------------------------------------

void Game::idle (void) const {

  usleep (DELAY*40);
  
}

//---------------------------------------------------------------------------

int Game::reasonEndGame (void) const {

  if (pressedQ)
    return 1;
  else if (player->hazDead ())
    return 2;
  else if (!alien->getLen ())
    return 3;
  else
    return 4;
  
}
