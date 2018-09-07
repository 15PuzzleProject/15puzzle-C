#ifndef PUZZLE_H
#define PUZZLE_H

#include <time.h>

struct puzzle {
  int table[16];
  int moves;
  int complete;
  time_t start_time;
  time_t end_time;
};

typedef struct puzzle Puzzle;

Puzzle* new_puzzle();

void reset();
void arrange();

int find(Puzzle* puzzle, int piece);

int can_move(Puzzle* puzzle, int piece);
void move(Puzzle* puzzle, int piece);

time_t get_time_taken(Puzzle* puzzle);

#endif
