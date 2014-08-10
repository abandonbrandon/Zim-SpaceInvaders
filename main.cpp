//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
using namespace std;

extern void drawSplashBegin (void);
extern void drawSplashEnd (int);

//User Classes
#include "Game.hpp"

int main (void) {

  Game start;

  drawSplashBegin ();

  do {
    
    start.drawActor ();
    refresh ();
    start.calculate ();
    start.getInput ();
    clear ();

  } while (!start.endGame ());

  drawSplashEnd (start.reasonEndGame ());

  endwin ();
  
}
