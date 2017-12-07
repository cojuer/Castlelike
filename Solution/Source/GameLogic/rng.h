#pragma once

class RNG
{
public:
    RNG();

    unsigned int getNext();
    int getInRange(int a, int b);
};