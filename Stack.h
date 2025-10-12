#include<iostream>
using namespace std;

template <class T>
class Stack
{
public:
    Stack() : top(nullptr) {};
    struct Node
    {
        T data;
        Node *next;
    };
    bool Push(T data); // Push returns the status code if push was successful/unsuccessful
    bool Pop(T &data); // Pop: returns the status code for success/unsuccess and //the value by reference
    bool Top(T &data); // Top: returns the top value by reference parameter and
    // status code (true/false) for success/failure
private:
    Node *top;      // Points to the top of the stack
    bool isEmpty(); // returns true if the stack is empty
};


// ---------------- Implementation ----------------

template <class T>
bool Stack<T>::isEmpty()
{
    return top == nullptr;
}

template <class T>
bool Stack<T>::Push(T data)
{
    Node *newNode = new Node;
    if (!newNode)
        return false;

    newNode->data = data;
    newNode->next = top;
    top = newNode;

    return true;
}

template <class T>
bool Stack<T>::Pop(T &data)
{
    if (isEmpty())
        return false;

    Node *temp = top;
    data = top->data;
    top = top->next;
    delete temp;

    return true;
}

template <class T>
bool Stack<T>::Top(T &data)
{
    if (isEmpty())
        return false;

    data = top->data;
    return true;
}
