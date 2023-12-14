#include "bloom.h"

#define size 50

int main() {
  bool bitarray[size] = { false };
  char* words[] = {"test", "test2", "math", "dsa",
                   "bloom", "bonus"}; 
  int c = 0;

  for (int i = 0; i < sizeof(words)/sizeof(words[0]); i++){
    bloom_insert(bitarray, size, words[i]);
    printf("Added element: %s\n", words[i]);
    c++;
  }
  printf("\n");


  printf("False positive possibility is %f%%\n", bloom_probability(size, c));

  char* checkupWords[] = {"test", "test2", "test3", "sda", "boom", "bones"};
  for (int i = 0; i < sizeof(checkupWords)/sizeof(checkupWords[0]); i++){
    if (bloom_lookup(bitarray, size, checkupWords[i]))
      printf("Word: %s probably in set\n", checkupWords[i]);
    else
      printf("Word: %s definetly not in set\n", checkupWords[i]);
  }
  return 0;
}
