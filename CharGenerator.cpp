#include "CharGenerator.h"
#include "Exception.h"
#include <random>


CharGenerator::CharGenerator()
{   //adds all possible directions to the array
    directions = new char[4];
    directions[0] = 'r';
    directions[1] = 'l';
    directions[2] = 'u';
    directions[3] = 'd';
    size = 4;
}

CharGenerator::~CharGenerator()
{
    delete[] directions;
    directions = nullptr; //good practice
}

bool CharGenerator::isEmpty() const
{
    return size == 0;
}

int CharGenerator::findIndex(char value) const
{   //returns the index if it exists, returns -1 if it does not
    for (int i = 0; i< size; i++)
    {
        if (directions[i] == value)
        {
            return i;
        }
    }
    return -1;
}

int CharGenerator::getSize() const
{
    return size;
}

void CharGenerator::removeIndex(int index)
{ //creates a new array without the given index value and assigns that array to directions array
    if (isEmpty())                              //this method will not be called when array is empty 
    {
        throw Exception("CharGenerator array is empty");
    }
    char * newDirections = new char[size-1];    //new array to store reduced directions
    int j = 0;                                  //will be used for index assigment to newDirections
    for (int i = 0; i< size; i++)
    {
        if (i != index)         //every element except that index is copied
        {
            newDirections[j] = directions[i]; 
            j++;    //index to assign is updated
        }
    }
    delete[] directions; //deletes the old array 
    directions = newDirections; //assigns to the new array
    size--;                                     //size is updated 
}

char CharGenerator::generateDirection() const
{ //generates a random direction in directions array
    if (isEmpty())              //this method will not be called when array is empty
    {
        throw Exception("CharGenerator array is empty");
    }
    int randomInt = rand.getRandomInt(size-1);                  //generates a random int
    return directions[randomInt];                               //returns a random direction
}

void CharGenerator::removeDirection(char direction)
{ //removes a given direction
    int index = findIndex(direction);
    if (index == -1)            //this condition should never happen in the implementation
    {
        throw Exception("Given character is not in the array");
    }
    removeIndex(index);     //removes the index
}

