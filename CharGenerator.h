#include <map>
#include <random>
#include "RandomInt.h"

using namespace std;

#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

class CharGenerator{
public:
    CharGenerator();                        //constructor
    ~CharGenerator();                       //destructor
    bool isEmpty() const;                   //returns true if array is empty
    int findIndex(char) const;              //finds the index of given character
    int getSize() const;                    //returns the size of the array
    void removeIndex(int);                  //removes an index from the array and creates a new array
    char generateDirection() const;         //generates a random direction from the array
    void removeDirection(char);             //removes a direction from the array



private:
    char* directions;   //this array will store the each char direction
    int size;           //holds the size of the array, necessary for number generation 
    RandomInt rand;     //this object will generate a random integer
};  

#endif
