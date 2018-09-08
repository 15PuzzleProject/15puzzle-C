#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "include/puzzle.h"
#include "include/io.h"
#include "include/save.h"

void game_loop() {
  srand(time(NULL));

  long highscore = load_score();

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

    int direction = get_direction(input);

    if(!p->complete) {
      if (can_move(p, direction)) {
        move(p, direction);
        strcpy(message, "");
      } else {
        strcpy(message, "Invalid move.");
      }

      if (p->complete) {
        time_t time_taken = get_time_taken(p);

        if (time_taken < highscore || -1 == highscore) {
          highscore = time_taken;
          save_score(highscore);
        }

        sprintf(message, "YOU WIN! Time: %d:%d (Best: %d:%d)", time_taken / 60, time_taken % 60, highscore / 60, highscore % 60);
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
