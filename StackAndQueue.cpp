#include "StackAndQueue.h"

//THIS WILL BE ONLY INCLUDED IN MAIN


template <class T>
Stack<T>::Stack()               //constructor
{
    size = 0;
    head = nullptr;
}

template <class T>
Stack<T>::~Stack()              //destructor
{
    while (head != nullptr)         //traverses each node in the stack
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr; //good practice
    }
}

template <class T>
void Stack<T>::Push(T value)                                                 //adds a T object to the top of the stack
{
    Node<T>* newNode = new Node<T>(value, head);        //Creates a new node and that node points to previous head
    if (newNode == nullptr)                             //protection against running out of memory
    {
        throw Exception("Out of heap!");
    }
    head = newNode;                                     //head points to the newly added node
    size++;                                             //updates the size
}

template <class T>
void Stack<T>::Pop()                                                   //removes and returns a T object from the top of the stack
{
    if(isEmpty())                      //in this assignment stack should never be empty when attempting to pop, it will throw an exception if it happens
    {
        throw Exception("Stack is empty");
    }
    Node<T>* poppedNode = head;         //node to be deleted
    head = head->next;                  //head is updated
    delete poppedNode;                  //previous head is deleted
    poppedNode = nullptr;               //good practice
    size--;                             //updates the size
}

template <class T>
T Stack<T>::Top() const                                     //returns the T object at the head of the stack
{ //this function will be called after calling isEmpty(), there is an exception handling just in case
    if(isEmpty())                //in this assignment stack should never be empty when attempting to top, it will throw an exception if it happens
    {
        throw Exception("Stack is empty");
    }
    return head->value;
}

template <class T>
bool Stack<T>::isEmpty() const  //returns true if empty
{
    return head == nullptr;
}

template <class T>
int Stack<T>::getSize() const   //returns the size
{
    return size;
}

template <class T>
Node<T>* Stack<T>::getHead() const      //returns the head
{
    return head;
}



template <class T>
Queue<T>::Queue()       //constructor
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
Queue<T>::~Queue()          //destructor
{
    while(head != nullptr)
    {
        Node<T> * temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
    tail = nullptr;
    head = nullptr;
}

template <class T>
void Queue<T>::Push(T value)                //pushes the value to the tail
{
    Node<T>* newNode = new Node<T>(value, nullptr);
    if (head == nullptr)        //if the first element
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;   //connects the previous tail with the newNode
        tail = newNode;         //tail becomes the newNode
    }
    size++;
}

template <class T>
T Queue<T>::Pop()
{
    if (isEmpty())          //this should not happen
    {
        throw Exception("Queue is empty, cannot pop!");
    }
    else
    {
        T object = head->value;     //gets the value of the head
        Node<T>* toBeDeleted = head;
        head = head->next;      //updates the head
        delete toBeDeleted;      //deletes the previous head
        toBeDeleted = nullptr;
        size--;
        return object;
    }
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return head == nullptr;
}

template <class T>
int Queue<T>::getSize() const
{
    return size;
}


template <class T>
Node<T>* Queue<T>::getHead() const
{
    return head;
}

