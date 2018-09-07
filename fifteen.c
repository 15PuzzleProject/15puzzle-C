#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "include/puzzle.h"
#include "include/io.h"

int pnumber(char piece) {
  switch(piece) {
    case ' ': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    default: return 0;
  };
}

void game_loop() {
  srand(time(NULL));

  char input;
  char* message = (char*) malloc(sizeof(char)*64);
  strcpy(message, "");

  Puzzle* p = new_puzzle();

  while(1) {
    system("clear");
    print_puzzle(p, message);

    scanf("%c", &input);
    if ('\n' == input) continue;
    input = map_input(input);

    if ('Q' == input){
      break;
    } else if ('R' == input) {
      reset(p);
      strcpy(message, "");
      continue;
    }

    int piece = pnumber(input);

    if(!p->complete) {
      if (can_move(p, piece)) {
        move(p, piece);
        strcpy(message, "");
      } else {
        strcpy(message, "Invalid move.");
      }

      if (p->complete) {
        time_t time_taken = get_time_taken(p);
        sprintf(message, "YOU WIN! Time: %d:%d", time_taken / 60, time_taken % 60);
      }
    }
  }

  printf("\nBye!\n\n");
  free(p);
  free(message);
}

int main() {
  game_loop();
}
