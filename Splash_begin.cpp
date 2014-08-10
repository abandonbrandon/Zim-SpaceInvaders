//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

void drawSplashBegin (void) {

  start_color ();

  ifstream sprite;
  sprite.open ("sprite_begin.txt");

  if (!sprite.is_open ()) {
    cerr << "Someone moved sprite_begin.txt :/"
         << "\nNot cool..." << endl;
    exit (1);
  }

  string line;

  int ypos (0);

  while (sprite.good ()) {

    getline (sprite,line);
    char ch;

    for (int xpos (0);xpos<62;xpos++) {
      ch = line[xpos];

      if (ch >= 65 && ch <= 90)
        mvaddch (ypos,xpos,ch | COLOR_PAIR (3));
      else if (ch == ':')
        mvaddch (ypos,xpos,ch | COLOR_PAIR (2));
      else
        continue;

    }
      
    ++ypos;

    if (ypos == 16)
      break;
    
  }

  attron (COLOR_PAIR (4));
  attron (A_BOLD);
  attron (A_UNDERLINE);
  mvaddstr (17,30,"[Press a key]");
  attroff (COLOR_PAIR (4));
  attroff (A_BOLD);
  attroff (A_UNDERLINE);

  move (0,0);
  refresh ();
  getchar ();
  nodelay (stdscr,true);
  
}
