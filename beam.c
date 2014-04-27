#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

#define DELAY 80000

//  | o   o |
//  | o-  o-|
//  | o-- o--
//  | o---o---
//  | o --- ---
//  | o  ---|---
//  | o   --- ---
//  | o   o--- ---
//  | o   o --- ---
//  | o   o |--- ---
//  | o   o | --- ---
//  | o   o |  --- ---

// options
int ONE_LINE   = 0;
int SIN_WAVE   = 0;
int BEAM_COUNT = 3;

// functions
void option(int argc, char *argv[]);
int beam(int t);

int main(int argc, char *argv[])
{
  int t = 0;

  option(argc, argv);

  initscr();

  while (true) {
    clear();
    if (beam(t++) == ERR) break;
    refresh();
    usleep(DELAY);
  }

  endwin();
  return 0;
}

void option(int argc, char *argv[])
{
  int result;
  while ((result = getopt(argc, argv, "osc:")) != -1) {
    switch (result) {
      case 'o': ONE_LINE = 1; break;
      case 's': SIN_WAVE = 1; break;
      case 'c': BEAM_COUNT = atoi(optarg); break;
    }
  }
}

int beam(int t)
{
  int sp = 9; // start position 
  t += sp;

  int c = BEAM_COUNT, i, disp[t], end_flag = 1;
  char ch[2] = {' ', '~'};


  for(i = 0; i < t; i++) disp[i] = 0;

  i = t;
  while (c-- && i > sp - 1) {
    if(i == sp) {
      disp[i-1] = 1; disp[i-5] = 1;
    } else if (t == sp + 1) {
      disp[i-1] = 1; disp[i-5] = 1;
      disp[i-2] = 1; disp[i-6] = 1;
    } else {
      disp[i-1] = 1; disp[i-5] = 1;
      disp[i-2] = 1; disp[i-6] = 1;
      disp[i-3] = 1; disp[i-7] = 1;
    }
    i -= 10;
  }

  for(i = 0; i < t && i < COLS; i++) {
    mvaddch(0, i, ch[disp[i]]);
  }

  if(end_flag) return ERR;

  return OK;
}

