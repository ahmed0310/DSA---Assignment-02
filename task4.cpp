#include <iostream>
#include <string>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node* next;
    Node(const T& val){
        data = val;
        next = nullptr;
    }
};

template <class T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    bool RemoveValue(const T& value);
public:
    Queue();
    ~Queue();
    bool isEmpty() const;
    bool Enqueue(const T& value);
    bool Dequeue(T& value);
    bool EnqueueAtFront(const T& value);
    void Display() const;
};

int main() {
    Queue<string> landingQueue;
    Queue<string> takeoffQueue;
    int choice;
    string flight;
    bool success;

    do {
        cout << endl << "----- AIR TRAFFIC CONTROL SYSTEM -----" << endl;
        cout << "1. Add Landing Request" << endl;
        cout << "2. Add Takeoff Request" << endl;
        cout << "3. Process Next Landing" << endl;
        cout << "4. Process Next Takeoff" << endl;
        cout << "5. Declare Emergency Landing" << endl;
        cout << "6. Display Queues" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter flight number for landing (e.g. PK301): ";
            cin >> flight;
            success = landingQueue.Enqueue(flight);
            if (success)
                cout << "Landing request added for " << flight << endl;
            else
                cout << "Failed to add request." << endl;
            break;
        case 2:
            cout << "Enter flight number for takeoff (e.g. PK210): ";
            cin >> flight;
            success = takeoffQueue.Enqueue(flight);
            if (success)
                cout << "Takeoff request added for " << flight << endl;
            else
                cout << "Failed to add request." << endl;
            break;
        case 3:
            if (landingQueue.isEmpty()) {
                cout << "No landing requests." << endl;
            } else {
                landingQueue.Dequeue(flight);
                cout << "Landing clearance given to " << flight << endl;
            }
            break;
        case 4:
            if (takeoffQueue.isEmpty()) {
                cout << "No takeoff requests." << endl;
            } else {
                takeoffQueue.Dequeue(flight);
                cout << "Takeoff clearance given to " << flight << endl;
            }
            break;
        case 5:
            cout << "Enter emergency flight number: ";
            cin >> flight;
            landingQueue.EnqueueAtFront(flight);
            cout << "Emergency landing request moved to front for " << flight << endl;
            break;
        case 6:
            cout << endl << "Landing Queue: ";
            landingQueue.Display();
            cout << "Takeoff Queue: ";
            takeoffQueue.Display();
            break;
        case 7:
            cout << "Exiting ATC system." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
    return 0;
}

//----------------- Queue Class Implementation ----------------

template <class T>
Queue<T>::Queue() {
    front = rear = nullptr;
}

template <class T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        T temp;
        Dequeue(temp);
    }
}

template <class T>
bool Queue<T>::isEmpty() const {
    return front == nullptr;
}

template <class T>
bool Queue<T>::Enqueue(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!newNode) return false;
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    return true;
}

template <class T>
bool Queue<T>::Dequeue(T& value) {
    if (isEmpty()) return false;
    Node<T>* temp = front;
    value = front->data;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;
    delete temp;
    return true;
}

template <class T>
bool Queue<T>::RemoveValue(const T& value) {
    if (isEmpty()) return false;
    Node<T>* curr = front;
    Node<T>* prev = nullptr;
    while (curr != nullptr) {
        if (curr->data == value) {
            if (prev == nullptr)
                front = curr->next;
            else
                prev->next = curr->next;
            if (curr == rear)
                rear = prev;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

template <class T>
bool Queue<T>::EnqueueAtFront(const T& value) {
    RemoveValue(value);
    Node<T>* newNode = new Node<T>(value);
    if (!newNode) return false;
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        newNode->next = front;
        front = newNode;
    }
    return true;
}

template <class T>
void Queue<T>::Display() const {
    if (isEmpty()) {
        cout << "Empty Queue" << endl;
        return;
    }
    Node<T>* temp = front;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr)
            cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
}