#include <stdlib.h>
#include <time.h>

#include "include/puzzle.h"
#include "include/util.h"

#define TRUE 1
#define FALSE 0

#define idx(l, c) (4*l+c)
#define lin(idx) (idx/4)
#define col(idx) (idx%4)

Puzzle* new_puzzle() {
  Puzzle* p = (Puzzle*) malloc(sizeof(Puzzle));
  reset(p);
  return p;
}

void arrange(Puzzle* p) {
  int i;
  for (i = 0 ; i < 16 ; i++) p->table[i] = i+1;
  p->table[15] = 0;
}

int is_feasible(Puzzle* p) {
  int *table = p->table;
  int inversions = 0;

  int i,j;
  for (i = 0 ; i < 14 ; i++)
    for (j = i+1 ; j < 15 ; j++)
      if (table[i] > table[j])
        inversions++;

  return (inversions % 2 == 0);
}

void randomize(Puzzle* puzzle) {
  int i;

  do {
    for (i = 0 ; i < 15 ; i++) {
      int value;
      do {
        value = 1 + (rand() % 15);
      } while (contains(puzzle->table, i, value));

      puzzle->table[i] = value;
    }
    puzzle->table[15] = 0;

  } while (!is_feasible(puzzle));
}

void reset(Puzzle* p) {
  p->moves = 0;
  p->start_time = 0;
  p->complete = FALSE;
  time(&p->start_time);
  randomize(p);
}

int find(Puzzle* puzzle, int piece) {
  int i;

  for (i = 0 ; i < 16 ; i++)
    if(piece == puzzle->table[i])
      return i;

  return -1;
}

void swap(Puzzle* puzzle, int p1, int p2) {
  int id1 = find(puzzle, p1);
  int id2 = find(puzzle, p2);

  puzzle->table[id1] = p2;
  puzzle->table[id2] = p1;
}

int is_complete(Puzzle* puzzle) {
  int i;

  for (i = 0 ; i < 15 ; i++)
    if (puzzle->table[i] != i+1)
      return FALSE;

  return TRUE;
}

int can_move(Puzzle* puzzle, int direction) {
  int s_idx, s_lin, s_col;

  // Space
  s_idx = find(puzzle, 0);
  s_lin = lin(s_idx);
  s_col = col(s_idx);

  switch (direction) {
    case UP:
      return (3 != s_lin);
    case DOWN:
      return (0 != s_lin);
    case LEFT:
      return (3 != s_col);
    case RIGHT:
      return (0 != s_col);
    default:
      return FALSE;
  }
}

void move(Puzzle* puzzle, int direction) {

  int offset, space_idx;

  switch (direction) {
    case UP:
      offset = 4;
      break;
    case DOWN:
      offset = -4;
      break;
    case LEFT:
      offset = 1;
      break;
    case RIGHT:
      offset = -1;
      break;
  }

  space_idx = find(puzzle, 0);
  puzzle->table[space_idx] = puzzle->table[space_idx + offset];
  puzzle->table[space_idx + offset] = 0;

  puzzle->complete = is_complete(puzzle);

  if (puzzle->complete)
    time(&puzzle->end_time);
}

time_t get_time_taken(Puzzle* puzzle) {
  if (puzzle->complete)
    return puzzle->end_time - puzzle->start_time;
  else
    return -1;
}
