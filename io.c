#include <stdio.h>

#include "include/io.h"
#include "include/puzzle.h"

char table_layout[] = "*---*---*---*---*\n| %c | %c | %c | %c |    THE 15-PUZZLE PROJECT: C\n*---*---*---*---*\n| %c | %c | %c | %c |    WASD to move\n*---*---*---*---*    [R]eset or [Q]uit\n| %c | %c | %c | %c |\n*---*---*---*---*\n| %c | %c | %c | %c |    %s\n*---*---*---*---*\n";
char pieces[16] = { ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char get_piece(Puzzle* puzzle, int index) {
  return pieces[puzzle->table[index]];
}

void print_puzzle(Puzzle* p, char *message) {
  printf(table_layout,
    get_piece(p,0), get_piece(p,1), get_piece(p,2), get_piece(p,3),
    get_piece(p,4), get_piece(p,5), get_piece(p,6), get_piece(p,7),
    get_piece(p,8), get_piece(p,9), get_piece(p,10), get_piece(p,11),
    get_piece(p,12), get_piece(p,13), get_piece(p,14), get_piece(p,15), message);
}

char map_input(char input) {
  switch (input) {
    case 'w': return 'W';
    case 'a': return 'A';
    case 's': return 'S';
    case 'd': return 'D';
    case 'q': return 'Q';
    case 'r': return 'R';
    default: return input;
  }
}

int get_direction(char input) {
  switch (input) {
    case 'W': return UP;
    case 'A': return LEFT;
    case 'S': return DOWN;
    case 'D': return RIGHT;
    default: return -1;
  }
}
