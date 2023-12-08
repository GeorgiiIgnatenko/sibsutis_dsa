#include "hash.h"

int hash1(char *key, int arrSize) {
  long long int h = 0;
  for (int i = 0; key[i] != '\0'; i++){
    h = (h * 127 + key[i]) % arrSize;
  }
  return h;
};

int hash2(char *key, int arrSize) {
  long long int hash = 0;
  for (int i = 0; key[i] != '\0'; i++)
  {
    hash = (hash + ((int)key[i]));
    hash = hash % arrSize;
  }
  return hash;
};

int hash3(char *key, int arrSize) {
  long long int hash = 1;
  for (int i = 0; key[i] != '\0'; i++){
    hash = hash + pow(19, i) * key[i];
    hash = hash % arrSize;
  }
  return hash % arrSize;
};

int hash4(char *key, int arrSize) {
  long long int hash = 3;
  int p = 7;
  for (int i = 0; key[i] != '\0'; i++){
    hash += hash * 7 + key[0] * pow(p, i);
    hash = hash % arrSize;
  }
  return hash;
};
