#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> s;
    int value;

    cout << "Pushing 10, 20 and 30..." << endl;
    s.Push(10);
    s.Push(20);
    s.Push(30);

    cout << endl << "Top element: ";
    if (s.Top(value))
        cout << value << endl;
    else
        cout << "Stack is empty." << endl;

    cout << endl << "Popping elements..." << endl;
    while (s.Pop(value))
    {
        cout << "Popped: " << value << endl;
    }

    cout << endl << "Trying to pop again..." << endl;
    if (!s.Pop(value))
        cout << "Stack is empty now." << endl;

    return 0;
}

