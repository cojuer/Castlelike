#include "rng.h"
#include <cstdlib>

RNG::RNG() {}

// TODO: rewrite
unsigned int RNG::getNext()
{
    return rand();
}

// TODO: rewrite
int RNG::getInRange(int a, int b)
{
    return b >= a ? rand() % (b - a + 1) + a : a;
}