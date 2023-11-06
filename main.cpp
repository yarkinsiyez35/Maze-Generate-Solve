#include <iostream>
#include "Maze.h"
#include "StackAndQueue.cpp"
#include "RandomInt.h"
#include <fstream>
#include <sstream>

using namespace std;


//YARKIN SIYEZ 30976

string toString(const int & i)  //converts int to string
{
    string str;
    stringstream stream;
    stream << i;
    stream >> str;
    return str;
}

void reverseStack(Stack<Coordinate>& stack) //the stack is reversed by using a queue 
{
    Queue<Coordinate> queue;
    while(!stack.isEmpty()) //pushes each element of stack to the queue 
    {
        Coordinate currentElement = stack.Top();
        stack.Pop();
        queue.Push(currentElement);
    }
    while(!queue.isEmpty())         //pushes each element of the queue to the stack 
    {
        Coordinate currentElement = queue.Pop();
        stack.Push(currentElement);
    }
}

void writeToFile(const string & filename, Stack<Coordinate> & stack) //writes to the given file by popping the elements of the stack 
{
    ofstream outputFile(filename); 
    if (outputFile.is_open())       
    {
        while (!stack.isEmpty())            //writes to the file 
        {
            Coordinate currentElement = stack.Top();
            stack.Pop();
            string content = toString(currentElement.x) + "," + toString(currentElement.y) + "\n";
            outputFile << content;
        }
    }
    else            //this should not happen
    {
        throw Exception("Cannot write to file " + filename);
    }
}

void writeToFile(const string & filename, const string & content) //writes the content to the given file
{
    ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        outputFile << content;
    }
    else
    {
        throw Exception("Cannot write to file " + filename);
    }
}

int main() {

    /*input output part*/
    cout << "Enter the number of mazes: ";
    int numberOfMazes;
    cin >> numberOfMazes;
    cout << "Enter the number of rows and columns (M and N): ";
    int numberOfRows, numberOfCols;
    cin >> numberOfRows >> numberOfCols;

    Maze* mazeArray = new Maze[numberOfMazes];          //an array is created to store all mazes

    for (int i = 0; i< numberOfMazes; i++)
    {
        try
        {
            Maze maze(numberOfRows,numberOfCols); //constructs a maze object with given inputs
            Stack<Coordinate> generatorStack; //this stack will be used to generate the maze
            maze.generateMaze(generatorStack); //maze is generated
            mazeArray[i] = maze; //maze is stored in the array
            string mazeFilename = "maze_"+  toString(i+1)+ ".txt"; //filename is created
            maze.printMaze(mazeFilename); //maze information is printed to mazeFilename
        }
        catch (Exception e) //if anything goes wrong, it will be caught
        {
            cout << e.getMessage() << endl;
        }
    }

    /*input output part*/
    cout << "Enter a maze ID between 1 to " << numberOfMazes << " inclusive to find a path: ";
    int mazeId;
    cin >> mazeId;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    int x1, y1;
    cin >> x1 >> y1;
    Coordinate entryCoordinate(x1,y1); //an object to store the given coordinates is created
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    int x2,y2;
    cin >> x2 >> y2;
    Coordinate exitCoordinate(x2,y2); //an object to store the given coordinates is created

    try
    { //tries to solve the maze
        Stack<Coordinate> solutionStack; //this stack will be used to solve the maze by storing the correct pathway at the end
        mazeArray[mazeId-1].solveMaze(solutionStack,entryCoordinate,exitCoordinate); //solves the maze
        reverseStack(solutionStack); //reverses the stack
        string solutionFileName = "maze_" + toString(mazeId)+ "_path_" + toString(entryCoordinate.x) + "_" + toString(entryCoordinate.y) +
                "_" + toString(exitCoordinate.x) + "_" + toString(exitCoordinate.y) + ".txt"; //the filename is created
        writeToFile(solutionFileName,solutionStack); //writes the solution to the file;

    }
    catch (Exception e) //if anything goes wrong, it will be caught
    {
        cout << e.getMessage() << endl;
    }

    delete[] mazeArray; //deletes the maze array since it was dynamically allocated
    mazeArray = nullptr;    //good practice

    return 0;
}
