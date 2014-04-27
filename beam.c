#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

// chikubi color
#define CHIKUBI_DEFAULT 0
#define CHIKUBI_PINK 1

// $ chikubeam
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
int BEAM_COUNT = 3;
int COLOR      = 0;
int SHAPE      = 0;
int DELAY      = 80000;
int WAVE_TYPE   = 0;

// functions
void option(int argc, char *argv[]);
void init_chikubi_color();
void print_chikubi();
int beam(int t);

int main(int argc, char *argv[])
{
  int t = 0;

  option(argc, argv);

  initscr();
  init_chikubi_color();

  // beam
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
  while ((result = getopt(argc, argv, "cfn:sw")) != -1) {
    switch (result) {
      case 'c': COLOR = 1; break;
      case 'f': DELAY = 40000; break;
      case 'n': BEAM_COUNT = atoi(optarg); break;
      case 's': SHAPE = 1; break;
      case 'w': WAVE_TYPE = 1; break;
    }
  }
}

void init_chikubi_color()
{
  if (!COLOR) return;

  if (has_colors() == FALSE || start_color() == ERR) {
    endwin();
    fprintf(stderr, "chikubi-color initialization failed.");
    exit(EXIT_FAILURE);
  }

  init_pair(CHIKUBI_DEFAULT, COLOR_WHITE, COLOR_BLACK);
  init_pair(CHIKUBI_PINK, COLOR_MAGENTA, COLOR_BLACK);
}

void print_chikubi()
{
  printw(" | ");

  if (COLOR) attrset(COLOR_PAIR(CHIKUBI_PINK));

  if (SHAPE) {
    printw("*   *");
  } else {
    printw("o   o");
  }

  if (COLOR) attrset(COLOR_PAIR(CHIKUBI_DEFAULT));

  printw(" | ");
}

int beam(int t)
{
  int sp = 9; // start position 
  t += sp;

  int c = BEAM_COUNT, i, disp[t], end_flag = 1;
  char wave = (WAVE_TYPE)? '~' : '-';

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

  // print
  print_chikubi();

  for (i = 0; i < t && i < COLS; i++) {
    if (disp[i]) {
      mvaddch(0, i, wave);
      end_flag = 0;
    }
  }

  if(end_flag) return ERR;
  return OK;
}

