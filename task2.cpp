#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Stack.h"
using namespace std;

// ---------------- Box Class ----------------
class Box
{
    static int uniqueTrackingIdGenerator;

public:
    float netWeight;
    int sourceCode;
    int destinationCode;
    int trackingId;

    Box(float w = 0, int s = 0, int d = 0);
    Box(const Box &other);
    friend ostream &operator<<(ostream &out, const Box &b);
    bool operator==(const Box &other) const;
    Box &operator=(const Box &other); // assignment operator
};
int Box::uniqueTrackingIdGenerator = 1000;

// ---------------- Warehouse Class ----------------
class Warehouse
{
private:
    Stack<Box> stacks[5];

public:
    void push(const Box &b);
    void pop(int stackNo);
    void search(int trackingId);
    void removeBox(int trackingId);
    void displayAll();
};

int main()
{
    srand(time(0));
    Warehouse wh;

    Box b1(12.5, 101, 202);
    Box b2(8.2, 103, 209);
    Box b3(15.7, 105, 210);
    Box b4(5.9, 108, 211);
    Box b5(9.0, 109, 213);

    cout << endl
         << "--- Adding Boxes ---" << endl;
    wh.push(b1);
    wh.push(b2);
    wh.push(b3);
    wh.push(b4);
    wh.push(b5);

    wh.displayAll();

    cout << endl
         << "--- Searching for Box 1003 ---" << endl;
    wh.search(1003);

    cout << endl
         << "--- Removing Box 1002 --- " << endl;
    wh.removeBox(1002);

    wh.displayAll();

    cout << endl
         << "--- Popping top box from Stack 3 ---" << endl;
    wh.pop(3);

    wh.displayAll();

    return 0;
}

// ---------------- Box Class Implementation ----------------

Box::Box(float w, int s, int d)
{
    uniqueTrackingIdGenerator++;
    netWeight = w;
    sourceCode = s;
    destinationCode = d;
    trackingId = uniqueTrackingIdGenerator;
}

Box::Box(const Box &other)
{
    netWeight = other.netWeight;
    sourceCode = other.sourceCode;
    destinationCode = other.destinationCode;
    trackingId = other.trackingId;
}

Box &Box::operator=(const Box &other)
{
    if (this != &other)
    {
        netWeight = other.netWeight;
        sourceCode = other.sourceCode;
        destinationCode = other.destinationCode;
        trackingId = other.trackingId;
    }
    return *this;
}

ostream &operator<<(ostream &out, const Box &b)
{
    out << "[Tracking ID: " << b.trackingId
        << ", Weight: " << b.netWeight
        << ", Source: " << b.sourceCode
        << ", Dest: " << b.destinationCode << "]";
    return out;
}

bool Box::operator==(const Box &other) const
{
    return trackingId == other.trackingId;
}

// ---------------- Warehouse Class Implementation ----------------
void Warehouse::push(const Box &b)
{
    int randomStack = rand() % 5;
    stacks[randomStack].Push(b);
    cout << "Box added to Stack " << randomStack + 1 << " " << b << endl;
}

void Warehouse::pop(int stackNo)
{
    Box temp;
    if (stackNo < 1 || stackNo > 5)
    {
        cout << "Invalid stack number!" << endl;
        return;
    }
    if (stacks[stackNo - 1].Pop(temp))
        cout << "Removed from Stack " << stackNo << ": " << temp << endl;
    else
        cout << "Stack " << stackNo << " is empty!" << endl;
}

void Warehouse::search(int trackingId)
{
    bool found = false;
    for (int i = 0; i < 5; i++)
    {
        Stack<Box> tempStack;
        Box temp;
        int count = 0;

        while (stacks[i].Pop(temp))
        {
            count++;
            if (temp.trackingId == trackingId)
            {
                cout << "Found in Stack " << i + 1
                     << " after removing " << (count - 1) << " boxes." << endl;

                found = true;
            }
            tempStack.Push(temp);
        }

        // Restore original stack
        while (tempStack.Pop(temp))
            stacks[i].Push(temp);
    }

    if (!found)
        cout << "Box with Tracking ID " << trackingId << " not found." << endl;
}

void Warehouse::removeBox(int trackingId)
{
    bool found = false;
    for (int i = 0; i < 5; i++)
    {
        Stack<Box> tempStack;
        Box temp;
        int count = 0;

        while (stacks[i].Pop(temp))
        {
            count++;
            if (temp.trackingId == trackingId)
            {
                cout << "Removed Box: " << temp
                     << " from Stack " << i + 1
                     << " after checking " << count << " boxes." << endl;
                found = true;
                break;
            }
            else
            {
                tempStack.Push(temp);
            }
        }

        Box restore;
        while (tempStack.Pop(restore))
            stacks[i].Push(restore);

        if (found)
            return;
    }

    if (!found)
        cout << "Box with Tracking ID " << trackingId << " not found." << endl;
}

void Warehouse::displayAll()
{
    cout << endl
         << "Current Warehouse State:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Stack " << i + 1 << ": ";
        Stack<Box> tempStack;
        Box temp;

        while (stacks[i].Pop(temp))
        {
            cout << temp << "  ";
            tempStack.Push(temp);
        }
        cout << endl;

        while (tempStack.Pop(temp))
            stacks[i].Push(temp);
    }
    cout << endl;
}
