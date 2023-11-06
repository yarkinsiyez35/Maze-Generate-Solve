#include <random>

#ifndef RANDOMINT_H
#define RANDOMINT_H


class RandomInt { //this class creates a random integer, it has no private members because it does not have to
public:
    RandomInt();                      //constructor
    int getRandomInt(int) const;                    //returns a random int
};


#endif
