#include "bloom.h"
#include "time.h"
#define size 500000

int main() {
  bool bitarray[size] = { false };

  char words[size/10][7];
  FILE *f = fopen("./data/out", "r");
  int i = 0;
  while(i < size/10){
    fscanf(f, "%s\n", words[i]);
    words[i][6] = '\0';
    i++;
  }
  fclose(f);
   
  printf("\n");

  FILE *out = fopen("./data/insertion_time.csv", "w");
  fprintf(out, "n,t,w\n");
  struct timespec start, end;
  for (int i = 0; i < sizeof(words)/sizeof(words[0]); i++){
    clock_gettime(CLOCK_MONOTONIC, &start);
    bloom_insert(bitarray, size, words[i]);
    clock_gettime(CLOCK_MONOTONIC, &end);
    long long duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    double durationInSec = (double)duration/1000000000;
    fprintf(out, "%d, %.9f, %s\n", i, durationInSec, words[i]);
  }
  fclose(out);
  printf("\n");

  out = fopen("./data/lookup_time.csv", "w");
  fprintf(out, "n,t,w\n");
  for (int i = 0; i < sizeof(words)/sizeof(words[0]); i++){
    clock_gettime(CLOCK_MONOTONIC, &start);
    bloom_lookup(bitarray, size, words[i]);
    clock_gettime(CLOCK_MONOTONIC, &end);
    long long duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    double durationInSec = (double)duration/1000000000;
    fprintf(out, "%d, %.9f, %s\n", i, durationInSec, words[i]);
  }
  fclose(out);
  printf("\n");

  printf("False positive possibility is %f%%\n", bloom_probability(size, i));

  return 0;
}
