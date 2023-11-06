#include "RandomInt.h"


RandomInt::RandomInt() {}


int RandomInt::getRandomInt(int range) const                //generates a random integer between 0 and given range 
{
    static std::random_device rd;
    std::uniform_int_distribution<int> dist (0,range);
    return dist(rd);
}
