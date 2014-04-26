#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

// options
int ONE_LINE   = 0;
int SIN_WAVE   = 0;
int BEAM_COUNT = 0;

// functions
void option(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  option(argc, argv);

  printf("ONE_LINE  : %d\n", ONE_LINE);
  printf("SIN_WAVE  : %d\n", SIN_WAVE);
  printf("BEAM_COUNT: %d\n", BEAM_COUNT);
  return 0;
}

void option(int argc, char *argv[])
{
  int result;
  while((result = getopt(argc, argv, "osc:")) != -1) {
    switch(result) {
      case 'o': ONE_LINE = 1; break;
      case 's': SIN_WAVE = 1; break;
      case 'c': BEAM_COUNT = atoi(optarg); break;
    }
  }
}

