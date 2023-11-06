
#ifndef CELL_H
#define CELL_H


//This class is responsible for holding the necessary information for every cell in the maze


class Cell
{
public:
    Cell();                                                                             //default constructor
    Cell(bool right, bool left, bool up, bool down, bool visited, int x, int y);        //parametric constructor
    bool getRight() const;      //returns existence of the right wall
    bool getLeft() const;       //returns existence of the left wall
    bool getUp() const;         //returns existence of the up wall
    bool getDown() const;       //returns existence of the down wall
    bool getVisited() const;    //returns the cell's visit status
    int getX() const;           //returns the x coordinate of the cell
    int getY() const;           //returns the y coordinate of the cell
    void setRight(bool);        //sets the existence of the right wall
    void setLeft(bool);         //sets the existence of the left wall
    void setUp(bool);           //sets the existence of the up wall
    void setDown(bool);         //sets the existence of the down wall
    void setVisited(bool);      //sets the cell's visit status
    void setX(int);             //sets the x coordinate of the cell
    void setY(int);             //sets the y coordinate of the cell
private:
    bool right, left, up, down, visited;  //wall directions and visited information 
    int x, y;               //coordinates   
};


#endif
