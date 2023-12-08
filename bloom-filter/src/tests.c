#include "bloom.h"
#include "time.h"
#include <bits/time.h>

#define size 500000

int main() {
  bool bitarray[size] = { false };

  char words[50000][7];
  FILE *f = fopen("./data/out", "r");
  int i = 1;
  while(i < 50001){
    fscanf(f, "%s\n", words[i]);
    i++;
  }
  fclose(f);
   
  printf("\n");

  FILE *out = fopen("./data/insertion_time.csv", "w");

  struct timespec start, end;
  for (int i = 0; i < sizeof(words)/sizeof(words[0]); i++){
    clock_gettime(CLOCK_MONOTONIC, &start);
    bloom_insert(bitarray, size, words[i]);
    clock_gettime(CLOCK_MONOTONIC, &end);
    long long duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    double durationInSec = (double)duration/1000000000;
    printf("Added element: %s\n", words[i]);
    printf("Estimated time: %.9f\n", durationInSec);
    fprintf(out, "%d, %.9f\n",i+1, durationInSec);
  }
  fclose(out);
  printf("\n");

  printf("False positive possibility is %f\%\n", bloom_probability(size, i));

  return 0;
}
