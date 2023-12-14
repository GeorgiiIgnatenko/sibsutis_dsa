#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "hash.h"

void bloom_insert(bool *bitarray, int arrSize, char *key);
bool bloom_lookup(bool *bitarray, int arrSize, char *key);
double bloom_probability(int arrSize, int elementsCount);
