#include "Exception.h"

#ifndef STACKANDQUEUE_H
#define STACKANDQUEUE_H

template <class T>
struct Node             //this node will hold any type of object
{
    T value;
    Node* next;

    Node(T value, Node* next)           //parametric constructor
    {
        this->value = value;
        this->next = next;
    }
};

template <class T>
class Stack       //this stack will hold any type of object
{
public:
    Stack();                        //constructor
    ~Stack();                       //destructor
    void Push(T value);             //pushes a t Object to the top of the stack
    void Pop();                     //removes the t Object from the top of the stack
    T Top() const;                  //returns the top element of the stack
    bool isEmpty() const;           //returns true if empty
    int getSize() const;            //returns the size of the stack
    Node<T>* getHead() const;       //returns the head of the stack
private:
    int size;
    Node<T>* head;
};



/*Queue class will be used to reverse the stack
 * this is necessary because the solution stack will hold the solution path in reverse order (end to beginning)
 */

template <class T>
class Queue{
public:
    Queue();                        //constructor
    ~Queue();                       //destructor
    void Push(T value);             //pushes an element to the end
    T Pop();                        //removes the element from the top
    bool isEmpty() const;           //returns true if empty
    int getSize() const;            //returns the size
    Node<T>* getHead() const;       //returns the head 

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

#endif //STACKANDQUEUE_H

