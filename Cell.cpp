#include "Cell.h"


Cell::Cell()
{   //on default every cell has 4 walls and is unvisited
    right = true;
    left = true;
    up = true;
    down = true;
    visited = false;
    x = 0;
    y = 0;
}

Cell::Cell(bool right, bool left, bool up, bool down, bool visited, int x, int y)
{ //this will be used in the creation of the maze
    this->right = right;
    this->left = left;
    this->up = up;
    this->down = down;
    this->visited = visited;
    this->x = x;
    this->y = y;
}

bool Cell::getRight() const
{
    return right;
}

bool Cell::getLeft() const
{
    return left;
}
bool Cell::getUp() const
{
    return up;
}
bool Cell::getDown() const
{
    return down;
}

bool Cell::getVisited() const
{
    return visited;
}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}

void Cell::setRight(bool input)
{
    this->right = input;
}

void Cell::setLeft(bool input)
{
    this->left = input;
}

void Cell::setUp(bool input)
{
    this->up = input;
}

void Cell::setDown(bool input)
{
    this->down = input;
}

void Cell::setVisited(bool input)
{
    this->visited = input;
}

void Cell::setX(int input)
{
    this->x = input;
}

void Cell::setY(int input)
{
    this->y = input;
}
