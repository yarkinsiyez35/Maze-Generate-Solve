#include "Maze.h"
#include "CharGenerator.h"
#include <iostream>
#include "Exception.h"

Maze::Maze()
{ //this constructor will not be used
    matrix = nullptr;
    numberOfRows = 0;
    numberOfCols = 0;
}

Maze::Maze(int rows, int cols)
{ //this constructor creates rows X cols matrix
    matrix = new Cell*[rows];                   //creates rows many Cell* array
    numberOfRows = rows;
    numberOfCols = cols;
    for (unsigned int i =0; i< rows; i++)
    {
       matrix[i] = new Cell[cols];                      //creates cols many Cell array
       for (unsigned int j = 0; j< cols; j++)
       {
           matrix[i][j] = Cell(true, true, true, true,false,j,i);               //each cell is unvisited, has all the walls, and has coordinate (j,i)
       }
    }
}

Maze::~Maze()
{ //destructor
    for (int i = 0; i< numberOfRows; i++)
    {
        delete[] matrix[i]; 
    }
    delete[] matrix;
    matrix = nullptr; //good practice
}

Maze::Maze(const Maze & rhs)
{ //deep copy constructor
    this->numberOfRows = rhs.numberOfRows;
    this->numberOfCols = rhs.numberOfCols;
    matrix = new Cell*[numberOfRows];
    for (int i = 0; i< numberOfRows ; i++)                  //copies every cell value to the new matrix
    {
        matrix[i] = new Cell[numberOfCols];
        for (int j = 0; j< numberOfCols; j++)
        {
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
}


Maze& Maze::operator=(const Maze &rhs){
    if (this != &rhs)
    {
        for (int i = 0; i < numberOfRows; i++)          //deletes the matrix
        {
            delete[] matrix[i];
        }
        delete[] matrix;

        numberOfRows = rhs.numberOfRows;
        numberOfCols = rhs.numberOfCols;


        matrix = new Cell *[numberOfRows];                  //copies the values from the rhs
        for (int i = 0; i < numberOfRows; i++) {
            matrix[i] = new Cell[numberOfCols];
            for (int j = 0; j < numberOfCols; j++) {
                matrix[i][j] = rhs.matrix[i][j];
            }
        }
    }
    return *this;
}

int Maze::getNumberOfRows() const
{
    return numberOfRows;
}
int Maze::getNumberOfCols() const
{
    return numberOfCols;
}

void Maze::breakLeft(Coordinate coordinate)
{
    matrix[coordinate.y][coordinate.x].setLeft(false);
}
void Maze::breakRight(Coordinate coordinate)
{
    matrix[coordinate.y][coordinate.x].setRight(false);
}
void Maze::breakDown(Coordinate coordinate)
{
    matrix[coordinate.y][coordinate.x].setDown(false);
}
void Maze::breakUp(Coordinate coordinate)
{
    matrix[coordinate.y][coordinate.x].setUp(false);
}
void Maze::setVisit(bool status, Coordinate coordinate)
{
    matrix[coordinate.y][coordinate.x].setVisited(status);
}
bool Maze::isVisited(Coordinate coordinate) const
{
    return matrix[coordinate.y][coordinate.x].getVisited();
}

bool Maze::possibleMove(Coordinate currentCoordinate, Coordinate nextCoordinate) const
{
    if (nextCoordinate.x < 0 || nextCoordinate.y < 0 || nextCoordinate.x >= numberOfCols || nextCoordinate.y >= numberOfRows)           //out of bounds check
    {
        return false;
    }
    return !isVisited(nextCoordinate);              //it is a possible move if that cell is not visited
}
void Maze::breakWalls(Coordinate currentCoordinate, char c1, Coordinate nextCoordinate, char c2)
{ //this function breaks the given wall for each Cell
    /*breaking the wall of the first cell*/
    if (c1 == 'r')
    {
        breakRight(currentCoordinate);
    }
    else if (c1 == 'l')
    {
        breakLeft(currentCoordinate);
    }
    else if (c1 == 'u')
    {
        breakUp(currentCoordinate);
    }
    else
    {
        breakDown(currentCoordinate);
    }

    /*breaking the wall of the second cell*/
    if (c2 == 'r')
    {
        breakRight(nextCoordinate);
    }
    else if (c2 == 'l')
    {
        breakLeft(nextCoordinate);
    }
    else if (c2 == 'u')
    {
        breakUp(nextCoordinate);
    }
    else
    {
        breakDown(nextCoordinate);
    }
}

Coordinate Maze::nextCell(Coordinate currentCoordinate)
{
    setVisit(true,currentCoordinate);                   //sets the current cell as visited

    CharGenerator charGenerator;                                        //this object will be used to generate directions
    int x1 = matrix[currentCoordinate.y][currentCoordinate.x].getX();
    int y1 = matrix[currentCoordinate.y][currentCoordinate.x].getY();
    bool searching = true;
    while (searching)                   //this loop will go on until one candidate is found or options are exhausted
    {
        char direction = charGenerator.generateDirection();         //a direction is generated
        if (direction == 'r')
        {
            Coordinate nextCoordinate = Coordinate(x1+1, y1);         //creates the coordinates of the next cell
            if (possibleMove(currentCoordinate,nextCoordinate))             //if there is a possible move between the two cells
            {
                return nextCoordinate;                                      //returns the valid cell
            }
            else                                                            //no possible move between those two cells
            {
                if (charGenerator.getSize() == 1)                           //no options are remaining
                {
                    searching = false;
                }
                else                                                        //the search goes on
                {
                    charGenerator.removeDirection(direction);               //removes that direction and one iteration ends
                }
            }
        }
        else if (direction == 'l')
        {
            Coordinate nextCoordinate = Coordinate(x1-1,y1);                //creates the coordinates of the next cell
            if (possibleMove(currentCoordinate,nextCoordinate))                   //if there is a possible move between the two cells
            {
                return nextCoordinate;                                            //returns the valid cell
            }
            else                                                                  //no possible move between those two cells
            {
                if (charGenerator.getSize() == 1)                                 //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                                                              //the search goes on
                {
                    charGenerator.removeDirection(direction);                    //removes that direction and one iteration ends
                }
            }
        }
        else if (direction == 'u')
        {
            Coordinate nextCoordinate = Coordinate(x1,y1 +1);           //creates the coordinates of the next cell
            if (possibleMove(currentCoordinate, nextCoordinate))              //if there is a possible move between the two cells
            {
                return nextCoordinate;                                        //returns the valid cell
            }
            else                                                              //no possible move between those two cells
            {
                if (charGenerator.getSize() == 1)                             //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                                                          //search goes on
                {
                    charGenerator.removeDirection(direction);                 //removes that direction and the iteration of loop ends
                }
            }
        }
        else                                                                 //direction == 'd'
        {
            Coordinate nextCoordinate = Coordinate(x1,y1-1);           //creates the coordinate of the next cell
            if (possibleMove(currentCoordinate,nextCoordinate))              //if there is a possible move between the two cells
            {
                return nextCoordinate;                                       //returns the valid cell
            }
            else
            {
                if (charGenerator.getSize() == 1)                            //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                    //search goes on
                {
                    charGenerator.removeDirection(direction);               //removes that direction and the iteration of loop ends
                }
            }
        }
    }
    return Coordinate(-1,-1);                                        //returns an invalid coordinate to initiate backtracking
}

void Maze::connectCells(Coordinate currentCoordinate, Coordinate nextCoordinate)
{ //the wall between two cells is broken down
    /*find which wall to break*/
    int xDifference = currentCoordinate.x - nextCoordinate.x;               //calculates the distance between x coordinates

    if (xDifference == 1)           //placement: x2 x1
    {
        breakWalls(currentCoordinate, 'l',nextCoordinate, 'r');
    }
    else if (xDifference == -1)    //placement: x1 x2
    {
        breakWalls(currentCoordinate, 'r',nextCoordinate, 'l');
    }
    else                //x's are equal
    {
        int yDifference = currentCoordinate.y- nextCoordinate.y;            //calculates the distance between y coordinates
        if (yDifference == 1) //placement y1
        {                               //y2
            breakWalls(currentCoordinate, 'd',nextCoordinate, 'u');
        }
        else                //placement y2
        {                             //y1
            breakWalls(currentCoordinate, 'u',nextCoordinate, 'd');
        }
    }
}
void Maze::generateMaze(Stack<Coordinate> & stack)
{ //generates the maze by backtracking
    Coordinate first = Coordinate(0, 0);
    int count = 0;                                                           //this will hold the number of visited cells
    int limit = getNumberOfRows() * getNumberOfCols();
    stack.Push(first);
    count++;
    while (count < limit) //this loop will go on until every cell is visited
    {
        Coordinate currentCoordinate = stack.Top();
        Coordinate nextCoordinate = nextCell(currentCoordinate); //finds the next coordinate to visit
        if (nextCoordinate.x == -1)        //if there is a not valid next cell
        {
            stack.Pop();            //current coordinates are removed since it cannot connect with a new cell, backtracking starts
        }
        else                        //there is a valid next cell
        {
            connectCells(currentCoordinate, nextCoordinate); //breaks the intersecting wall between two cells
            count++;                                         //updates the count
            stack.Push(nextCoordinate);                //adds to the stack as the current coordinate
        }
    }
    unvisitCells();                                          //unvisits every cell, this is needed to solve the maze later on
}
void Maze::printMaze(std::string & filename) const
{ //prints the maze information to the given file
    std::ofstream outputFile(filename); //creates a file stream

    if (outputFile.is_open())
    { //writes to the file
        outputFile << numberOfRows << " " << numberOfCols << std::endl;
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfCols; j++) {
                outputFile << "x=" << j << " y=" << i << " l=" << matrix[i][j].getLeft()
                           << " r=" << matrix[i][j].getRight() << " u=" << matrix[i][j].getUp()
                           << " d=" << matrix[i][j].getDown() << std::endl;
            }
        }

        outputFile.close(); //file is closed
    } else //if file fails to open
    {
        throw Exception("Failed to write maze information to the file");
    }
}

void Maze::unvisitCells()
{ //unvisits every cell in a matrix
    for (int i = 0; i<numberOfRows; i++)
    {
        for (int j =0; j< numberOfCols; j++)
        {
            Coordinate currentCoordinate = Coordinate (j,i);
            setVisit(false,currentCoordinate);
        }
    }
}

bool Maze::wallBetween(Coordinate currentCoordinate, Coordinate nextCoordinate) const
{ //this function returns the existence of wall between two coordinates, there is no need to check both of the cells since maze is generated successfully
    int xDifference = currentCoordinate.x - nextCoordinate.x;           //calculates the x coordinate difference of the cells
    if (xDifference == 1)               //placement: x2 x1
    {
        return matrix[currentCoordinate.y][currentCoordinate.x].getLeft();
    }
    else if (xDifference == -1)             //placement x1 x2
    {
        return matrix[currentCoordinate.y][currentCoordinate.x].getRight();
    }
    else
    {
        int yDifference = currentCoordinate.y - nextCoordinate.y;       //calculates the x coordinate difference of the cells
        if (yDifference == 1)       //placement y1
        {                                    // y2
            return matrix[currentCoordinate.y][currentCoordinate.x].getDown();
        }
        else                        //placement y2
        {                                    // y1
            return matrix[currentCoordinate.y][currentCoordinate.x].getUp();
        }
    }
}
bool Maze::possibleStep(Coordinate currentCoordinate,Coordinate nextCoordinate) const
{ //it is a possible step when there are no walls between the cells, next cell is not visited and next cell's coordinates are in bounds
    if (nextCoordinate.x <0 || nextCoordinate.y <0 || nextCoordinate.x >= numberOfCols || nextCoordinate.y >= numberOfRows)         //out of bounds control
    {
        return false;
    }
    return !(wallBetween(currentCoordinate, nextCoordinate) || matrix[nextCoordinate.y][nextCoordinate.x].getVisited());


}

Coordinate Maze::nextStep(Coordinate currentCoordinate)
{
    setVisit(true,currentCoordinate);           //sets the current cell as visited

    CharGenerator charGenerator;                                //this object will generate random directions
    int x1 = matrix[currentCoordinate.y][currentCoordinate.x].getX();
    int y1 = matrix[currentCoordinate.y][currentCoordinate.x].getY();
    bool searching = true;
    while (searching)                   //this loop will go on until one candidate is found or options are exhausted
    {
        char direction = charGenerator.generateDirection();         //a direction is generated
        if (direction == 'r')
        {
            Coordinate nextCoordinate = Coordinate(x1+1,y1);    //creates the coordinates of the next cell
            if (possibleStep(currentCoordinate,nextCoordinate))      //if there is a possible move between the two cells
            {
                return nextCoordinate;          //returns the valid cell
            }
            else
            {
                if (charGenerator.getSize() == 1)           //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                    //the search goes on
                {
                    charGenerator.removeDirection(direction);                   //removes that direction and the iteration of loop ends
                }
            }
        }
        else if (direction == 'l')
        {
            Coordinate nextCoordinate = Coordinate(x1-1,y1);            //creates the coordinates of the next cell
            if (possibleStep(currentCoordinate, nextCoordinate))             //if there is a possible move between the two cells
            {
                return nextCoordinate;                           //returns the valid cell
            }
            else
            {
                if (charGenerator.getSize() == 1)                   //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                                                    //search goes on
                {
                    charGenerator.removeDirection(direction);
                }
            }
        }
        else if (direction == 'u')
        {
            Coordinate nextCoordinate = Coordinate(x1,y1+1);            //creates the coordinates of the next cell
            if (possibleStep(currentCoordinate,nextCoordinate))             //if there is a possible move between the two cells
            {
                return nextCoordinate;                           //returns the valid cell
            }
            else
            {
                if (charGenerator.getSize() == 1)           //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                //search goes on
                {
                    charGenerator.removeDirection(direction);                   //removes that direction and the iteration of loop ends
                }
            }
        }
        else                //direction == 'd'
        {
            Coordinate nextCoordinate = Coordinate(x1,y1-1);                //creates the coordinates of the next cell
            if (possibleStep(currentCoordinate, nextCoordinate))                //if there is a possible move between the two cells
            {
                return nextCoordinate;                                      //returns the valid cell
            }
            else
            {
                if (charGenerator.getSize() == 1)               //the direction was the only remaining object in array
                {
                    searching = false;
                }
                else                    //search goes on
                {
                    charGenerator.removeDirection(direction);               //removes that direction and the iteration of loop ends
                }
            }
        }
    }
    return Coordinate(-1,-1);               //returns an invalid coordinate to initiate backtracking
}

void Maze::solveMaze(Stack<Coordinate> & stack, const Coordinate & start, const Coordinate& end)
{ //solves the maze by using a stack
    bool solving = true;
    stack.Push(start);
    while(solving)
    {
        Coordinate currentCoordinate = stack.Top();
        Coordinate nextCoordinate = nextStep(currentCoordinate); //finds the next cell's coordinates
        if(currentCoordinate == end)        //if they are equal, maze is solved
        {
            solving = false;
        }
        else if(nextCoordinate.x == -1)              //if there is not a valid step
        {   //starts backtracking
            stack.Pop();
        }
        else
        {
            stack.Push(nextCoordinate);          //adds to the stack as the current coordinate
        }
    }
}