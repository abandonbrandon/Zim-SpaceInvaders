//System header files
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

void drawSplashEnd (int type) {

  if (type == 1)
    return;

  ifstream sprite;

  if (type == 3) {

    sprite.open ("sprite_end_win.txt");

    if (!sprite.is_open ()) {
      cerr << "Someone moved sprite_end_win.txt :/"
           << "\nNot cool..." << endl;
      exit (1);
    }

    string line;

    int ypos (0);

    while (sprite.good ()) {

      getline (sprite,line);
      char ch;

      for (int xpos (0);xpos<41;xpos++) {
        ch = line[xpos];
        if (ch >= 32 && ch <= 126)
          mvaddch (ypos,xpos,ch | COLOR_PAIR (2));

      }
      
      ++ypos;

      if (ypos == 8)
        break;
    
    }

    attron (COLOR_PAIR (4));
    attron (A_BOLD);
    attron (A_UNDERLINE);
    mvaddstr (17,30,"You Win!");
    attroff (COLOR_PAIR (4));
    attroff (A_BOLD);
    attroff (A_UNDERLINE);

    move (0,0);
    refresh ();
    getchar ();
    nodelay (stdscr,true);
    
  }
  
  else {

    string reason;

    if (type == 2)
      reason = "You died...";
    else if (type == 4)
      reason = "Aliens have touched down!";


    sprite.open ("sprite_end_lose.txt");

    if (!sprite.is_open ()) {
      cerr << "Someone moved sprite_end_lose.txt :/"
           << "\nNot cool..." << endl;
      exit (1);
    }

    string line;

    int ypos (0);

    while (sprite.good ()) {

      getline (sprite,line);
      char ch;

      for (int xpos (0);xpos<75;xpos++) {
        ch = line[xpos];

        if (ch == 36)
          mvaddch (ypos,xpos,ch | COLOR_PAIR (3));
        else if (ch == ':')
          mvaddch (ypos,xpos,ch | COLOR_PAIR (2));
        else
          continue;

      }
      
      ++ypos;

      if (ypos == 9)
        break;
    
    }

    int length = (type==2)?11:25;

    for (int a (0);a<length;a++) {
      attron (COLOR_PAIR (4));
      attron (A_BOLD);
      attron (A_UNDERLINE);
      mvaddch (17,30+a,reason[a]);
      attroff (COLOR_PAIR (4));
      attroff (A_BOLD);
      attroff (A_UNDERLINE);
    }

    move (0,0);
    refresh ();
    getchar ();
    nodelay (stdscr,true);

  }
  
}
