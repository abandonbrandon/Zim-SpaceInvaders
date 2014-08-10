//System libraries
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
using namespace std;

//User Classes
#include "Object.hpp"
#include "Tuple.hpp"
#include "Shield.hpp"
#include "ShieldBlock.hpp"

ShieldBlock::ShieldBlock (Tuple* pos) {

  int place[]={2,3,4,8,9,10,11,12,14,15,16,17,18,19,20,21,22,26,27};
  shields = new Shield*[19];
  int iniY = pos->getL ();
  int iniX = pos->getR ();;
  
  for (int a (0);a<19;a++) {
    Tuple temp (Tuple (iniY + (place[a]/ 7), iniX+place[a] % 7));
    shields[a] = new Shield (&temp);
  }

  lenShields = 19;

  Pos = new Tuple (pos->getL (),pos->getR ());
}

//------------------------------------------------------------------------------

ShieldBlock::ShieldBlock (Tuple pos) {

  int place[]={2,3,4,8,9,10,11,12,14,15,16,17,18,19,20,21,22,26,27};
  shields = new Shield*[19];
  int iniY = pos.getL ();
  int iniX = pos.getR ();;
  
  for (int a (0);a<19;a++) {
    Tuple temp (Tuple (iniY + (place[a]/ 7), iniX+place[a] % 7));
    shields[a] = new Shield (&temp);
  }

  lenShields = 19;

  Pos = new Tuple;
  *Pos = pos;
}


//------------------------------------------------------------------------------

ShieldBlock::~ShieldBlock (void) {

  for (int a (0);a<19;a++) {
    if (shields[a] != NULL)
      delete shields[a];
  }

  delete[] shields;
  delete Pos;
    
}

//------------------------------------------------------------------------------

void ShieldBlock::draw (void) const {

  if (!lenShields)
    return;
  
  for (int a (0);a<19;a++) {
    if (shields[a] != NULL)
      shields[a]->draw ();
  }
}

//------------------------------------------------------------------------------

void ShieldBlock::removeDead (void) {

  for (int a (0);a<19;a++)
    if (shields[a] != NULL)
      if (shields[a]->getHit ()) {
        delete shields[a];
        shields[a] = NULL;
        break;
      }

}

//------------------------------------------------------------------------------

int ShieldBlock::getShields (void) const {

  return lenShields;
  
}

//------------------------------------------------------------------------------

void ShieldBlock::setHit (int num) {

  shields[num]->dead ();
  
}

//------------------------------------------------------------------------------

bool ShieldBlock::collision (Tuple* tup)  {

  return this->collision (*tup);
      
}

//------------------------------------------------------------------------------

bool ShieldBlock::collision (const Tuple& tup) {

  if (!lenShields)
    return false;
  
  bool beenHit=false;
  for (int a (0);a<19;a++) {
    if (shields[a] == NULL)
      continue;
    if (tup == shields[a]->getPos ()) {
      this->setHit (a);
      beenHit = true;
      break;
    }
  }
  
  if (beenHit) {
    --lenShields;
    this->removeDead ();
  }

  return beenHit;

    
}

//------------------------------------------------------------------------------

bool ShieldBlock::inVicinity (const Tuple& tup) const {

  int y_pos = tup.getL ();
  int x_pos = tup.getR ();

  int y_min = Pos->getL ();
  int y_max = y_min+4;

  int x_min = Pos->getR ();
  int x_max = x_min+7;

  return (y_min <= y_pos) && (y_pos <= y_max) && (x_min <= x_pos) && (x_pos <= x_max);
  
}

//------------------------------------------------------------------------------

bool ShieldBlock::inVicinity (Tuple* tup) const {

  return this->inVicinity (*tup);
  
}
