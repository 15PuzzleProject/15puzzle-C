#include <stdlib.h>

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

int can_move(Puzzle* puzzle, int piece) {
  int s_idx, s_lin, s_col, p_idx, p_lin, p_col;

  // Space
  s_idx = find(puzzle, 0);
  s_lin = lin(s_idx);
  s_col = col(s_idx);

  // Piece
  p_idx = find(puzzle, piece);
  p_lin = lin(p_idx);
  p_col = col(p_idx);

  int horizontal = (p_lin == s_lin) && ((p_col == s_col+1) || (p_col == s_col-1));
  int vertical = (p_col == s_col) && ((p_lin == s_lin+1) || (p_lin == s_lin-1));

  return (horizontal || vertical);
}

void move(Puzzle* puzzle, int piece) {
  swap(puzzle, piece, 0);
  puzzle->complete = is_complete(puzzle);
}
