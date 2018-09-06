#include "include/util.h"

int contains(int* array, int limit, int value) {
  int i;

  for (i = 0 ; i < limit ; i++)
    if (array[i] == value)
      return 1;

  return 0;
}
