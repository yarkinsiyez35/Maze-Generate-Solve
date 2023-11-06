#include "Cell.h"
#include "StackAndQueue.h"
#include <fstream>
#include <string>

#ifndef MAZE_H
#define MAZE_H

struct Coordinate           //this will be used to return the coordinate of the cell
{ //this class is used to use the coordinates of the cell in maze operations.
    int x;
    int y;
    Coordinate()        //default constructor
    {
        x = 0;
        y = 0;
    }
    Coordinate(int x, int y): x(x), y(y){}          //parametric constructor 
    bool operator==(const Coordinate& rhs) const    //equality comparison 
    {
        return x == rhs.x && y == rhs.y;
    }
};


class Maze{
public:
    Maze();                                                                         //dummy constructor, this will never be used
    Maze(int rows, int cols);                                                       //parametric constructor
    Maze(const Maze & rhs);                                                         //copy constructor
    ~Maze();                                                                        //destructor
    Maze & operator=(const Maze & rhs);                                             //will be used to store many mazes in Maze array, this is necessary since this class is using pointers for the matrix
    int getNumberOfRows() const;                                                    //returns the number of rows
    int getNumberOfCols() const;                                                    //returns the number of cols
    void breakLeft(Coordinate);                                                     //breaks the left wall of the given Cell Coordinate
    void breakRight(Coordinate);                                                    //breaks the right wall of the given Cell Coordinate
    void breakUp(Coordinate);                                                       //breaks the up wall of the given Cell Coordinate
    void breakDown(Coordinate);                                                     //breaks the down wall of the given Cell Coordinate
    void setVisit(bool,Coordinate);                                                 //sets the visit attribute of the given Cell Coordinate
    bool isVisited(Coordinate) const;                                               //returns the visit attribute of the given Cell Coordinate
    bool possibleMove(Coordinate, Coordinate) const ;                               //returns true if there is a possible move between 2 Coordinates
    void breakWalls(Coordinate, char, Coordinate, char);                            //breaks the intersecting wall between 2 Coordinates
    Coordinate nextCell(Coordinate);                                                //returns the next possible Cell Coordinate from the given Cell Coordinate
    void connectCells(Coordinate, Coordinate);                                      //connects two Cell Coordinates by breaking the intersecting wall
    void generateMaze(Stack<Coordinate> &);                                         //generates the maze with using a stack
    void printMaze(std::string &) const;                                            //prints the maze information to a text file
    void unvisitCells();                                                            //unvisits every cell, this is necessary to solve the maze
    bool wallBetween(Coordinate,Coordinate) const;                                  //checks if there is a wall between two cells
    bool possibleStep(Coordinate,Coordinate) const;                                 //check if a step can be made for the solution
    Coordinate nextStep(Coordinate) ;                                               //returns the next cell for the solution
    void solveMaze(Stack<Coordinate> &, const Coordinate &, const Coordinate&);     //solves the maze with using a stack

private:
    Cell** matrix;                  //this will hold the maze 
    int numberOfRows;               //stores number of rows 
    int numberOfCols;               //stores number of columns 
};

#endif
