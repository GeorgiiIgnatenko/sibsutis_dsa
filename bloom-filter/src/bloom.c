#include "bloom.h"

#define hash_count 4

void bloom_init() {};

void bloom_insert(bool *bitarray, int arrSize, char *key) {
  if (bloom_lookup(bitarray, arrSize, key))
    printf("%s is Probably already present", key);
  else{
    int a = hash1(key, arrSize);
    int b = hash2(key, arrSize);
    int c = hash3(key, arrSize);
    int d = hash4(key, arrSize);

   bitarray[a] = true;
   bitarray[b] = true;
   bitarray[c] = true;
   bitarray[d] = true;
  }
};

bool bloom_lookup(bool *bitarray, int arrSize, char *key) {
  int a = hash1(key, arrSize);
  int b = hash2(key, arrSize);
  int c = hash3(key, arrSize);
  int d = hash4(key, arrSize);

  if (bitarray[a] && bitarray[b] && bitarray[c] && bitarray[d]){ 
    return true;
  }else {
    return false;
  }
};

double bloom_probability(int arrSize, int elementsCount){
 long double falseProbability = 0.0;

 falseProbability = pow((1 - pow((1 - 1.0/arrSize),hash_count*elementsCount)),hash_count);

  return falseProbability;
}
