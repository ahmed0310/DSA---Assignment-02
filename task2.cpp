#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Stack.h"  
using namespace std;

class Box {
public:
    float netWeight;
    int sourceCode;
    int destinationCode;
    int trackingId;

    Box() {}
    Box(float w, int s, int d, int t) {
        netWeight = w;
        sourceCode = s;
        destinationCode = d;
        trackingId = t;
    }

    // Operator overloading for display
    friend ostream& operator<<(ostream& out, const Box& b) {
        out << "[Tracking ID: " << b.trackingId
            << ", Weight: " << b.netWeight
            << ", Source: " << b.sourceCode
            << ", Dest: " << b.destinationCode << "]";
        return out;
    }

    bool operator==(const Box& other) const {
        return trackingId == other.trackingId;
    }
};

class Warehouse {
private:
    Stack<Box> stacks[5]; // 5 stacks

public:
    Warehouse() { srand(time(0)); }

    void push(Box b) {
        int randomStack = rand() % 5;
        stacks[randomStack].Push(b);
        cout << "Box added to Stack " << randomStack + 1 << " " << b << endl;
    }

    void pop(int stackNo) {
        Box temp;
        if (stackNo < 1 || stackNo > 5) {
            cout << "Invalid stack number!" << endl;
            return;
        }
        if (stacks[stackNo - 1].Pop(temp))
            cout << "Removed from Stack " << stackNo << ": " << temp << endl;
        else
            cout << "Stack " << stackNo << " is empty!" << endl;
    }

    void search(int trackingId) {
        bool found = false;
        for (int i = 0; i < 5; i++) {
            Stack<Box> tempStack;
            Box temp;
            int count = 0;
            bool success;

            while (stacks[i].Pop(temp)) {
                count++;
                if (temp.trackingId == trackingId) {
                    cout << "Found in Stack " << i + 1
                         << " after removing " << (count - 1) << " boxes." << endl;
                    found = true;
                }
                tempStack.Push(temp);
            }

            while (tempStack.Pop(temp)) {
                stacks[i].Push(temp);
            }
        }

        if (!found)
            cout << "Box with Tracking ID " << trackingId << " not found." << endl;
    }

    void removeBox(int trackingId) {
        bool found = false;
        for (int i = 0; i < 5; i++) {
            Stack<Box> tempStack;
            Box temp;
            int count = 0;

            while (stacks[i].Pop(temp)) {
                count++;
                if (temp.trackingId == trackingId) {
                    cout << "Removed Box: " << temp
                         << " from Stack " << i + 1
                         << " after checking " << count << " boxes." << endl;
                    found = true;
                    break;
                } else {
                    tempStack.Push(temp);
                }
            }

            // Restore remaining boxes
            Box restore;
            while (tempStack.Pop(restore)) {
                stacks[i].Push(restore);
            }

            if (found) return;
        }

        if (!found)
            cout << "Box with Tracking ID " << trackingId << " not found." << endl;
    }

    void displayAll() {
        cout << "\nCurrent Warehouse State:\n";
        for (int i = 0; i < 5; i++) {
            cout << "Stack " << i + 1 << ": ";
            Stack<Box> tempStack;
            Box temp;
            while (stacks[i].Pop(temp)) {
                cout << temp << "  ";
                tempStack.Push(temp);
            }
            cout << endl;

            // restore
            while (tempStack.Pop(temp))
                stacks[i].Push(temp);
        }
        cout << endl;
    }
};


int main() {
    Warehouse wh;

    Box b1(12.5, 101, 202, 1001);
    Box b2(8.2, 103, 209, 1002);
    Box b3(15.7, 105, 210, 1003);
    Box b4(5.9, 108, 211, 1004);
    Box b5(9.0, 109, 213, 1005);

    cout << "\n--- Adding Boxes ---\n";
    wh.push(b1);
    wh.push(b2);
    wh.push(b3);
    wh.push(b4);
    wh.push(b5);

    wh.displayAll();

    cout << "\n--- Searching for Box 1003 ---\n";
    wh.search(1003);

    cout << "\n--- Removing Box 1002 ---\n";
    wh.removeBox(1002);

    wh.displayAll();

    cout << "\n--- Popping top box from Stack 3 ---\n";
    wh.pop(3);

    wh.displayAll();

    return 0;
}
