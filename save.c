#include <stdio.h>

#include "include/save.h"

void save_score(long int score) {
  FILE *file = fopen("save.15p", "wb");
  fwrite(&score, sizeof(long int), 1, file);
  fclose(file);
}

long int load_score() {
  FILE *file;
  long int score;

  if ((file = fopen("save.15p", "rb")) != NULL) {
    fread(&score, sizeof(long int), 1, file);
    fclose(file);
    return score;
  } else {
    return -1;
  }
}
