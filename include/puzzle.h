#ifndef PUZZLE_H
#define PUZZLE_H

struct puzzle {
  int table[16];
  int moves;
  int complete;
  long start_time;
};

typedef struct puzzle Puzzle;

Puzzle* new_puzzle();

void reset();
void arrange();

int find(Puzzle* puzzle, int piece);

int can_move(Puzzle* puzzle, int piece);
void move(Puzzle* puzzle, int piece);

#endif
