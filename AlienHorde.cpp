//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

#include <iostream>
using namespace std;

//User Classes
#include "Alien1.hpp"
#include "Alien2.hpp"
#include "Alien3.hpp"
#include "AlienHorde.hpp"

int DIR (int direction) {
  if (direction == 1)
    return -1;
  else
    return 1;
}

AlienHorde::AlienHorde (Tuple pos) {

  Pos = new Tuple (pos.getL (),pos.getR ());
  alien1 = new Alien1*[20];
  alien2 = new Alien2*[20];
  alien3 = new Alien3*[20];

  len1 = 20;
  len2 = 10;
  len3 = 10;
  len = 40;
  dir = 1;
  hasShifted = false;

  allDead1 = false;
  allDead2 = false;
  allDead3 = false;
  allDead = false;

  topLeft = new Tuple (pos.getL (),pos.getR ());
  botRight = new Tuple (pos.getL ()+6,pos.getR ()+10);

  int y_pos = pos.getL ();
  int x_pos = pos.getR ();

  for (int a (0);a<10;a++) {
    alien3[a] = new Alien3 (Tuple (y_pos,x_pos+(a*4)));
    alien3[a]->setID (a);
  }

  y_pos += 2;
  
  for (int b (0);b<10;b++) {
    alien2[b] = new Alien2 (Tuple (y_pos,x_pos+(b*4)));
    alien2[b]->setID (b+10);
  }

  y_pos += 2;
  
  for (int c (0);c<20;c++) {
    if (c == 10)
      y_pos += 2;
    alien1[c] = new Alien1 (Tuple (y_pos,x_pos+((c%10)*4)));
    alien1[c]->setID (20+c);
  }

  
  deadlings = new int[40];
  for (int a (0);a<40;a++)
    deadlings[a] = -1;
  
  Tuple posTmp[40];
  for (int d (0);d<40;d++)
    posTmp[d] = Tuple (-1,-1);

  posOfDead = new List (posTmp,40);
  lenDead = 0;
  
}

//------------------------------------------------------------------------------

AlienHorde::~AlienHorde (void) {

  delete Pos;
  
  if (topLeft != NULL)
    delete topLeft;

  if (botRight != NULL)
    delete botRight;

  if (allDead)
    return;

  if (!allDead1) {

    for (int a (0);a<10;a++)
      if (alien1[a] != NULL)
        delete alien1[a];
    delete[] alien1;
  }

  if (!allDead2) {

    for (int a (0);a<10;a++)
      if (alien2[a] != NULL)
        delete alien2[a];
    delete[] alien2;
  }

  if (!allDead3) {

    for (int a (0);a<10;a++)
      if (alien3[a] != NULL)
        delete alien3[a];
    delete[] alien3;
  }

  delete[] deadlings;
  delete posOfDead;

}

//------------------------------------------------------------------------------

bool AlienHorde::collision1 (const Tuple& pos, int& id) {

  if (allDead1 || !this->inVicinity1 (pos) || alien1 == NULL) {
    id = -1;
    return false;
  }

  bool hit (false);
  
  for (int a (0);a<20;a++)
    if (alien1[a] != NULL)
      if (alien1[a]->hit (pos)) {
        
        alien1[a]->death ();
        id = alien1[a]->getID ();
        hit = true;
        break;
      }

  if (!hit) {
    id = -1;
    return false;
  }

  this->removeDead1 ();

  return true;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::collision2 (const Tuple& pos, Projectile* proj, int &id) {

  if (allDead2 || !this->inVicinity2 (pos) || alien2 == NULL) {
    id = -1;
    return false;
  }

  bool hit (false);
  
  for (int a (0);a<10;a++)
    if (alien2[a] != NULL)
      if (alien2[a]->hit (pos)) {
        
        alien2[a]->reduceHealth (proj);
        hit = true;
        break;
      }

  if (!hit) {
    id = -1;
    return false;
  }

  this->removeDead2 (id);

  return true;
  
}


//------------------------------------------------------------------------------

bool AlienHorde::collision3 (const Tuple& pos, Projectile* proj, int &id) {

  if (allDead3 || !this->inVicinity3 (pos) || alien3 == NULL) {
    id = -1;
    return false;
  }

  bool hit (false);
  
  for (int a (0);a<10;a++)
    if (alien3[a] != NULL)
      if (alien3[a]->hit (pos)) {
        
        alien3[a]->reduceHealth (proj);
        hit = true;
        break;
      }

  if (!hit) {
    id = -1;
    return false;
  }

  this->removeDead3 (id);

  return true;

}

//------------------------------------------------------------------------------

bool AlienHorde::collision (const Tuple& pos, Projectile* proj, int &id) {

  if (allDead) {
    id = -1;
    return false;
  }
  
  if (this->inVicinity1 (pos))
    this->collision1 (pos,id);
  else if (this->inVicinity2 (pos))
    this->collision2 (pos,proj,id);
  else if (this->inVicinity3 (pos))
    this->collision3 (pos,proj,id);
  else {
    id = -1;
    return false;
  }

  return true;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::collision (Tuple* pos, Projectile* proj, int &id) {

  return this->collision (*pos,proj,id);
  
}

//------------------------------------------------------------------------------

void AlienHorde::removeDead1 (void) {

  if (allDead1 || alien1 == NULL)
    return;
  
  bool hasDied (false);
  
  for (int a (0);a<20;a++)
    if (alien1[a] != NULL)
      
      if (alien1[a]->hazDead ()) {
        posOfDead->replace (alien1[a]->getPos ()+Tuple (0,1),lenDead);
        deadlings[lenDead] = alien1[a]->getID ();
        ++lenDead;
        
        delete alien1[a];
        alien1[a] = NULL;
        hasDied = true;
        break;
      }

  if (!hasDied) {
    return;
  }

  --len1;
  --len;
  
  if (len1 <= 0) {
    allDead1 = true;
    delete[] alien1;
    alien1 = NULL;
    return;
  }

  if (len <= 0) {
    allDead = true;
    return;
  }
  
}

//------------------------------------------------------------------------------

void AlienHorde::removeDead2 (int &id) {

  if (allDead2 || alien2 == NULL) {
    id = -1;
    return;
  }

  bool hasDied (false);
  
  for (int a (0);a<10;a++)
    if (alien2[a] != NULL)
      
      if (alien2[a]->hazDead ()) {
        posOfDead->replace (alien2[a]->getPos ()+Tuple (0,1),lenDead);
        deadlings[lenDead] = alien2[a]->getID ();
        ++lenDead;

        id = alien2[a]->getID ();
        delete alien2[a];
        alien2[a] = NULL;
        hasDied = true;
        break;
      }

  if (!hasDied) {
    id = -1;
    return;
  }

  --len2;
  --len;

  if (len2 <= 0) {
    allDead2 = true;
    delete[] alien2;
    alien2 = NULL;
    return;
  }

  if (len <= 0) {
    allDead = true;
    return;
  }
  
}

//------------------------------------------------------------------------------

void AlienHorde::removeDead3 (int &id) {

  if (allDead3 || alien3 == NULL) {
    id = -1;
    return;
  }

  bool hasDied (false);
  
  for (int a (0);a<10;a++)
    if (alien3[a] != NULL)
      
      if (alien3[a]->hazDead ()) {
        posOfDead->replace (alien3[a]->getPos ()+Tuple (0,1),lenDead);
        deadlings[lenDead] = alien3[a]->getID ();
        ++lenDead;

        id = alien3[a]->getID ();
        delete alien3[a];
        alien3[a] = NULL;
        hasDied = true;
        break;
      }

  if (!hasDied) {
    id = -1;
    return;
  }

  --len3;
  --len;

  if (len3 <= 0) {
    allDead3 = true;
    delete[] alien3;
    alien3 = NULL;
    return;
  }

  if (len <= 0) {
    allDead = true;
    return;
  }
  
}

//------------------------------------------------------------------------------

void AlienHorde::draw1 (void) const {

  if (allDead1 || alien1 == NULL)
    return;

  attron (COLOR_PAIR (1));
  for (int a (0);a<20;a++) {
    if (alien1[a] == NULL)
      continue;
    
    alien1[a]->draw ();
  }
  attroff (COLOR_PAIR (1));
}

//------------------------------------------------------------------------------

void AlienHorde::draw2 (void) const {

  if (allDead2 || alien2 == NULL)
    return;
  
  attron (COLOR_PAIR (2));
  for (int a (0);a<10;a++) {
    if (alien2[a] == NULL)
      continue;
    
    alien2[a]->draw ();
  }
  attroff (COLOR_PAIR (2));
}

//------------------------------------------------------------------------------

void AlienHorde::draw3 (void) const {

  if (allDead3 || alien3 == NULL)
    return;

  attron (COLOR_PAIR (3));
  for (int a (0);a<10;a++) {
    if (alien3[a] == NULL)
      continue;
    
    alien3[a]->draw ();
  }
  attron (COLOR_PAIR (3));  
}

//------------------------------------------------------------------------------

void AlienHorde::draw (void) const {

  if (allDead)
    return;

  this->draw1 ();
  this->draw2 ();
  this->draw3 ();
  
}

//------------------------------------------------------------------------------

bool AlienHorde::touchDown1 (void) const {

  if (allDead1 || alien1 == NULL)
    return false;

  for (int a (0);a<20;a++)
    if (alien1[a] != NULL)
      if (alien1[a]->hasTouchedDown ())
        return true;

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::touchDown2 (void) const {

  if (allDead2 || alien2 == NULL)
    return false;

  for (int a (0);a<10;a++)
    if (alien2[a] != NULL)
      if (alien2[a]->hasTouchedDown ())
        return true;

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::touchDown3 (void) const {

  if (allDead3 || alien3 == NULL)
    return false;

  for (int a (0);a<10;a++)
    if (alien3[a] != NULL)
      if (alien3[a]->hasTouchedDown ())
        return true;

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::touchDown (void) const {

  if (allDead)
    return false;
  
  return this->touchDown1 () || this->touchDown2 () || this->touchDown3 ();
  
}

//------------------------------------------------------------------------------

void AlienHorde::shift1 (void) {

  if (this->touchDown1 () || allDead1 || alien1 == NULL)
    return;

  for (int a (0);a<20;a++) {

    if (alien1[a] == NULL)
      continue;
    alien1[a]->shift ();
  }
  
}

//------------------------------------------------------------------------------

void AlienHorde::shift2 (void) {

  if (this->touchDown2 () || allDead2 || alien2 == NULL)
    return;

  for (int a (0);a<10;a++) {

    if (alien2[a] == NULL)
      continue;
    alien2[a]->shift ();
  }
  
}

//------------------------------------------------------------------------------

void AlienHorde::shift3 (void) {

  if (this->touchDown3 () || allDead3 || alien3 == NULL)
    return;

  for (int a (0);a<10;a++) {

    if (alien3[a] == NULL)
      continue;
    alien3[a]->shift ();
  }

  
}

//------------------------------------------------------------------------------

void AlienHorde::shift (void) {

  if (this->touchDown () || allDead)
    return;

  this->shift1 ();
  this->shift2 ();
  this->shift3 ();
  
}

//------------------------------------------------------------------------------

void AlienHorde::move1 (void) {

  if (allDead1 || this->touchDown1 () || alien1 == NULL)
    return;

  for (int a (0);a<20;a++)
    if (alien1[a] != NULL)
      alien1[a]->updatePos ();
      
}

//------------------------------------------------------------------------------

void AlienHorde::move2 (void) {

  if (allDead2 || this->touchDown2 () || alien2 == NULL)
    return;

  for (int a (0);a<10;a++)
    if (alien2[a] != NULL)
      alien2[a]->updatePos ();
      
}

//------------------------------------------------------------------------------

void AlienHorde::move3 (void) {

  if (allDead3 || this->touchDown3 () || alien3 == NULL)
    return;

  for (int a (0);a<10;a++)
    if (alien3[a] != NULL)
      alien3[a]->updatePos ();
      
}

//------------------------------------------------------------------------------

void AlienHorde::move (void) {

  if (allDead || this->touchDown ())
    return;

  this->move1 ();
  this->move2 ();
  this->move3 ();
      
}

//------------------------------------------------------------------------------

bool AlienHorde::updatePos (void) {

  if (topLeft != NULL || botRight != NULL)
    if ((topLeft->getR () <= 0 || botRight->getR () >= 60) && !hasShifted) {
      this->shift ();
      
      *Pos = Tuple (Pos->getL ()+1, Pos->getR ());
      this->setCorners ();
      hasShifted = true;
      return false;
    }
  
    else {
      if (hasShifted) {
        dir = DIR (dir);
        hasShifted = false;
      }
      this->move ();
      *Pos = Tuple (Pos->getL (), Pos->getR ()+dir);
      this->setCorners ();
      return true;
    }

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::inVicinity1 (const Tuple& tup) const {

  if (allDead1 || this->touchDown1 () || alien1 == NULL)
    return false;

  int y_pos = tup.getL ();

  int y_min = topLeft->getL ()+4;
  int y_max = botRight->getL ()+6;
  
  bool passedY = (y_pos <= y_max) && (y_pos >= y_min);

  return passedY;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::inVicinity2 (const Tuple& tup) const {

  if (allDead2 || this->touchDown2 () || alien2 == NULL)
    return false;
  
  int y_pos = tup.getL ();

  int y = topLeft->getL ()+2;

  return (y_pos == y);
  
}

//------------------------------------------------------------------------------

bool AlienHorde::inVicinity3 (const Tuple& tup) const {

  if (allDead3 || this->touchDown3 () || alien3 == NULL)
    return false;
  
  int y_pos = tup.getL ();
  int y = topLeft->getL ();

  return (y_pos == y);
  
}

//------------------------------------------------------------------------------

bool AlienHorde::inVicinity (const Tuple& tup) const {

  if (allDead || this->touchDown ())
    return false;
  
  return this->inVicinity1 (tup) || this->inVicinity2 (tup) || this->inVicinity3 (tup);
  
}

//------------------------------------------------------------------------------

bool AlienHorde::inVicinity (Tuple* tup) const {

  return this->inVicinity (*tup);
  
}

//------------------------------------------------------------------------------

void AlienHorde::fire1 (int xpos, int &num, int* &ar, List* &li) const {

  if (allDead1 || alien1 == NULL) {
    num = 0;
    li = NULL;
    ar = NULL;
    return;
  }

  int tmp[20];
  int counter (-1);
  Tuple tup[20];

  for (int a (0);a<20;a++)
    if (alien1[a] != NULL)
      if (alien1[a]->canHazFire (xpos)) {

        ++counter;
        tmp[counter] = alien1[a]->getID ();
        tup[counter] = alien1[a]->getPos ();
      }

  if (counter == -1) {
    num = 0;
    ar = NULL;
    li = NULL;

    return;
  }

  ++counter;
  num = counter;
  ar = new int[counter];


  Tuple fin[num];
  
  for (int b (0);b<num;b++)
    fin[b] = tup[b];
  
  li = new List (fin,num);

  for (int c (0);c<num;c++)
    ar[c] = tmp[c];

}

//------------------------------------------------------------------------------

void AlienHorde::fire2 (int xpos, int &num, int* &ar, List* &li) const {

  if (allDead2 || alien2 == NULL) {
    num = 0;
    li = NULL;
    ar = NULL;
    return;
  }

  int tmp[10];
  int counter (-1);
  Tuple tup[10];
  
  for (int a (0);a<10;a++)
    if (alien2[a] != NULL)
      if (alien2[a]->canHazFire (xpos)) {

        ++counter;
        tmp[counter] = alien2[a]->getID ();
        tup[counter] = alien2[a]->getPos ();
      }

  if (counter == -1) {
    num = 0;
    ar = NULL;
    li = NULL;
    return;
  }

  ++counter;
  num = counter;
  ar = new int[num];

  Tuple fin[num];
  
  for (int b (0);b<num;b++)
    fin[b] = tup[b];
  
  li = new List (fin,num);

  for (int c (0);c<num;c++)
    ar[c] = tmp[c];

}


//------------------------------------------------------------------------------

void AlienHorde::fire3 (int xpos, int &num, int* &ar, List* &li) const {

  if (allDead3 || alien3 == NULL) {
    num = 0;
    li = NULL;
    ar = NULL;
    return;
  }
    
  int tmp[10];
  int counter (-1);
  Tuple tup[10];
  
  for (int a (0);a<10;a++)
    if (alien3[a] != NULL)
      if (alien3[a]->canHazFire (xpos)) {

        ++counter;
        tmp[counter] = alien3[a]->getID ();
        tup[counter] = alien3[a]->getPos ();
      }

  if (counter == -1) {
    num = 0;
    ar = NULL;
    li = NULL;
    return;
  }

  ++counter;
  num = counter;
  ar = new int[num];

  Tuple fin[num];
  
  for (int b (0);b<num;b++)
    fin[b] = tup[b];
  
  li = new List (fin,num);

  for (int c (0);c<num;c++)
    ar[c] = tmp[c];

}


//------------------------------------------------------------------------------

void AlienHorde::fire (int xpos, int &num, int* &ar, List* &li) const {

  int num1;
  int num2;
  int num3;

  int* ar1;
  int* ar2;
  int* ar3;

  List* li1;
  List* li2;
  List* li3;

  this->fire3 (xpos,num3,ar3,li3);
  this->fire2 (xpos,num2,ar2,li2);
  this->fire1 (xpos,num1,ar1,li1);

  num = num1 + num2 + num3;

  if (!num) {
    ar = NULL;
    li = NULL;
    return;
  }
    
  ar = new int[num];
  li = new List (1);

  for (int c (0);c<num3;c++)
    ar[c] = ar3[c];

  for (int b (0);b<num2;b++)
    ar[b+num3] = ar2[b];
  
  for (int a (0);a<num1;a++)
    ar[a+num3+num2] = ar1[a];

  if (num3)
    *li = *li3;
  if (num2 && !num3)
    *li = *li2;
  else if (num2 && num3)
    li->append (*li2);
  if (num1 && !num2 && !num3)
    *li = *li1;
  else if (num1 && (num2 || num3))
    li->append (*li1);

  if (ar1 != NULL)
    delete[] ar1;
  if (ar2 != NULL)
    delete[] ar2;
  if (ar3 != NULL)
    delete[] ar3;

  if (li1 != NULL)
    delete li1;
  if (li2 != NULL)
    delete li2;
  if (li3 != NULL)
    delete li3;

}

//------------------------------------------------------------------------------

void AlienHorde::powerCatalog (bool* &filt) const {

  filt = new bool[40];

  for (int a (0);a<10;a++)
    filt[a] = alien3[a]->getPowerState ();

  for (int b (0);b<10;b++)
    filt[b+10] = alien2[b]->getPowerState ();

  for (int c (0);c<20;c++)
    filt[c+20] = alien1[c]->getPowerState ();

}

//------------------------------------------------------------------------------

int AlienHorde::getDir (void) const {

  return dir;
  
}

//------------------------------------------------------------------------------

int AlienHorde::getLen (void) const {

  return len;
  
}

//------------------------------------------------------------------------------

void AlienHorde::setCorners (void) {

  this->setTL ();
  this->setBR ();
  
}

//------------------------------------------------------------------------------

void AlienHorde::setTL (void) {

  if (allDead) {
    delete topLeft;
    topLeft = NULL;
    return;
  }

  if (topLeft == NULL)
    return;
  
  int col1 (40);
  int col2 (40);
  int col3 (40);

  int idx1;
  int idx2;
  int idx3;

  if (!allDead3)
    for (int a (0);a<10;a++)
      if (alien3[a] != NULL) {
        col3 = alien3[a]->getPos (true);
        idx3 = a;
        break;
      }

  if (!allDead2)
    for (int a (0);a<10;a++)
      if (alien2[a] != NULL) {
        col2 = alien2[a]->getPos (true);
        idx2 = a;
        break;
      }
  
  if (!allDead1)
    for (int a (0);a<20;a++)
      if (alien1[a] != NULL) {
        col1 = alien1[a]->getPos (true);
        idx1 = a;
        break;
      }

  if (col1 < col2 && col1 < col3 && col1 != 40)
    *topLeft = Tuple (alien1[idx1]->getPos (false),col1);
  else if (col2 < col3 && col2 < col1 && col2 != 40)
    *topLeft = Tuple (alien2[idx2]->getPos (false),col2);
  else 
    *topLeft = Tuple (alien3[idx3]->getPos (false),col3);


}

//------------------------------------------------------------------------------

void AlienHorde::setBR (void) {

  if (allDead) {
    delete botRight;
    botRight = NULL;
    return;
  }

  if (botRight == NULL)
    return;

  int col1a (-1);
  int col1b (-1);
  int col2 (-1);
  int col3 (-1);

  int idx1a;
  int idx1b;
  int idx2;
  int idx3;

  if (!allDead3)
    for (int a (9);a>=0;a--)
      if (alien3[a] != NULL) {
        col3 = alien3[a]->getPos (true);
        idx3 = a;
        break;
      }

  if (!allDead2)
    for (int a (9);a>=0;a--)
      if (alien2[a] != NULL) {
        col2 = alien2[a]->getPos (true);
        idx2 = a;
        break;
      }
  
  if (!allDead1) {
    for (int a (19);a>=10;a--)
      if (alien1[a] != NULL) {
        col1a = alien1[a]->getPos (true);
        idx1a = a;
        break;
      }

    for (int b (9);b>=0;b--)
      if (alien1[b] != NULL) {
        col1b = alien1[b]->getPos (true);
        idx1b = b;
        break;
      }

  }

  int columns[4] = {col1a,col1b,col2,col3};

  int largest (col1a);

  for (int c (1);c<4;c++)
    if (largest < columns[c])
      largest = columns[c];

  if (largest == col1a)
    *botRight = Tuple (alien1[idx1a]->getPos (false),col1a);
  else if (largest == col1b)
    *botRight = Tuple (alien1[idx1b]->getPos (false),col1b);
  else if (largest == col2)
    *botRight = Tuple (alien2[idx2]->getPos (false),col2);
  else
    *botRight = Tuple (alien3[idx3]->getPos (false),col3);
  
}

//------------------------------------------------------------------------------

bool AlienHorde::hitConst1 (const Tuple& tup) const {

  if (allDead1 || alien1 == NULL)
    return false;
  
  for (int a (0);a<20;a++) {
    if (alien1[a] == NULL)
      continue;
    if (alien1[a]->hit (tup)) {
      return true;
    }
  }

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::hitConst2 (const Tuple& tup) const {

  if (allDead2 || alien2 == NULL)
    return false;
  
  for (int a (0);a<10;a++) {
    if (alien2[a] == NULL)
      continue;
    
    if (alien2[a]->hit (tup)) {
      return true;
    }
  }

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::hitConst3 (const Tuple& tup) const {

  if (allDead3 || alien3 == NULL)
    return false;
  
  for (int a (0);a<10;a++) {
    if (alien3[a] == NULL)
      continue;
    
    if (alien3[a]->hit (tup)) {
      return true;
    }
  }

  return false;
  
}

//------------------------------------------------------------------------------

bool AlienHorde::hitConst (const Tuple& tup) const {

  bool hazHit = this->hitConst1 (tup) || this->hitConst2 (tup) || this->hitConst3 (tup);

  return hazHit;
  
}

//------------------------------------------------------------------------------

Tuple AlienHorde::posbyID1 (int num) const{

  if (allDead1 || alien1 == NULL)
    return Tuple (0,0);

  for (int a (0);a<20;a++)
    if (alien1[a] != NULL)
      if (alien1[a]->getID () == num)
        return alien1[a]->getPos ();

  return Tuple (0,0);
  
}

//------------------------------------------------------------------------------

Tuple AlienHorde::posbyID2 (int num) const {

  if (allDead2 || alien2 == NULL)
    return Tuple (0,0);

  for (int a (0);a<10;a++)
    if (alien2[a] != NULL)
      if (alien2[a]->getID () == num)
        return alien2[a]->getPos ();

  return Tuple (0,0);

  
}

//------------------------------------------------------------------------------

Tuple AlienHorde::posbyID3 (int num) const {

  if (allDead3 || alien3 == NULL)
    return Tuple (0,0);

  for (int a (0);a<10;a++)
    if (alien3[a] != NULL)
      if (alien3[a]->getID () == num)
        return alien3[a]->getPos ();

  return Tuple (0,0);

  
}

//------------------------------------------------------------------------------

Tuple AlienHorde::posbyID (int num) const {

  Tuple tmp = this->posbyID1 (num) + this->posbyID2 (num) + this->posbyID3 (num);

  if (Tuple (0,0) == tmp)
    for (int a (0);a<lenDead;a++) {
      if (num == deadlings[a])
        return posOfDead->getTup (a);
    }

  return tmp;
}

//------------------------------------------------------------------------------

void AlienHorde::getArea (int id, List* &area) const {

  for (int b (0);b<lenDead;b++)
    if (id == deadlings[b]) {
      area = NULL;
      return;
    }
  
  Tuple tmp[3];
  
  if (id < 10) {
    if (allDead3 || alien3 == NULL) {
      area = NULL;
      return;
    }
      
    for (int c (0);c<10;c++)
      if (alien3[c] != NULL)
      
        if (id == alien3[c]->getID ()) {
          for (int a (0);a<3;a++) 
            tmp[a] = Tuple (alien3[c]->getPos (false), alien3[c]->getPos (true)+a);
          break;
        }
  }

  else if (id < 20) {
    if (allDead2 || alien2 == NULL) {
      area = NULL;
      return;
    }
      
    for (int c (0);c<10;c++)
      if (alien2[c] != NULL)
      
        if (id == alien2[c]->getID ()) {
          for (int a (0);a<3;a++) 
            tmp[a] = Tuple (alien2[c]->getPos (false), alien2[c]->getPos (true)+a);
          break;
        }
  }    


  else if (id >= 20 && id < 40) {
    if (allDead1 || alien1 == NULL) {
      area = NULL;
      return;
    }
    
    for (int c (0);c<20;c++)
      if (alien1[c] != NULL)
        
        if (id == alien1[c]->getID ()) {
          for (int a (0);a<3;a++) 
            tmp[a] = Tuple (alien1[c]->getPos (false), alien1[c]->getPos (true)+a);
          break;
        }
  }

  else {
    area = NULL;
    return;
  }
      
  area = new List (tmp,3);
  return;
      
}
