#ifndef IO_H
#define IO_H

#include "puzzle.h"

char get_piece(Puzzle* puzzle, int index);
void print_puzzle(Puzzle* p, char *message);

char map_input(char input);

#endif
