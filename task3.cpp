#include <iostream>
using namespace std;

// ---------------- Deque Class Declaration ----------------
template <class T>
class Deque {
private:
    int front;
    int rear;
    int size;
    T *arr;

public:
    Deque(int s = 5);
    ~Deque();

    bool isFull() const;
    bool isEmpty() const;

    bool EnqueueAtFront(const T &value);
    bool EnqueueAtRear(const T &value);
    bool DequeueFront(T &value);
    bool DequeueRear(T &value);
    bool Front(T &value) const;
    bool Rear(T &value) const;
    void Display() const;
};

int main() {
    Deque<int> dq(5);
    int choice, value;
    bool success;

    do {
        cout << endl << "----- DEQUE MENU -----" << endl;
        cout << "1. Enqueue at Front" << endl;
        cout << "2. Enqueue at Rear" << endl;
        cout << "3. Dequeue from Front" << endl;
        cout << "4. Dequeue from Rear" << endl;
        cout << "5. View Front" << endl;
        cout << "6. View Rear" << endl;
        cout << "7. Display Deque" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            success = dq.EnqueueAtFront(value);
            dq.Display();
            break;

        case 2:
            cout << "Enter value: ";
            cin >> value;
            success = dq.EnqueueAtRear(value);
            dq.Display();
            break;

        case 3:
            success = dq.DequeueFront(value);
            if (success)
                cout << "Deleted: " << value << endl;
            dq.Display();
            break;

        case 4:
            success = dq.DequeueRear(value);
            if (success)
                cout << "Deleted: " << value << endl;
            dq.Display();
            break;

        case 5:
            success = dq.Front(value);
            if (success)
                cout << "Front element: " << value << endl;
            break;

        case 6:
            success = dq.Rear(value);
            if (success)
                cout << "Rear element: " << value << endl;
            break;

        case 7:
            dq.Display();
            break;

        case 8:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 8);

    return 0;
}


// ---------------- Deque Class Implementation ----------------
template <class T>
Deque<T>::Deque(int s) {
    size = s;
    arr = new T[size];
    front = -1;
    rear = -1;
}

template <class T>
Deque<T>::~Deque() {
    delete[] arr;
}

template <class T>
bool Deque<T>::isFull() const {
    return ((front == 0 && rear == size - 1) || (front == rear + 1));
}

template <class T>
bool Deque<T>::isEmpty() const {
    return (front == -1);
}

template <class T>
bool Deque<T>::EnqueueAtFront(const T &value) {
    if (isFull()) {
        cout << "Deque is full. Cannot insert at front." << endl;
        return false;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else if (front == 0) {
        front = size - 1;
    } else {
        front--;
    }

    arr[front] = value;
    cout << value << " inserted at front." << endl;
    return true;
}

template <class T>
bool Deque<T>::EnqueueAtRear(const T &value) {
    if (isFull()) {
        cout << "Deque is full. Cannot insert at rear." << endl;
        return false;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else if (rear == size - 1) {
        rear = 0;
    } else {
        rear++;
    }

    arr[rear] = value;
    cout << value << " inserted at rear." << endl;
    return true;
}

template <class T>
bool Deque<T>::DequeueFront(T &value) {
    if (isEmpty()) {
        cout << "Deque is empty. Cannot delete from front." << endl;
        return false;
    }

    value = arr[front];

    if (front == rear) {
        front = rear = -1;
    } else if (front == size - 1) {
        front = 0;
    } else {
        front++;
    }

    cout << value << " deleted from front." << endl;
    return true;
}

template <class T>
bool Deque<T>::DequeueRear(T &value) {
    if (isEmpty()) {
        cout << "Deque is empty. Cannot delete from rear." << endl;
        return false;
    }

    value = arr[rear];

    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = size - 1;
    } else {
        rear--;
    }

    cout << value << " deleted from rear." << endl;
    return true;
}

template <class T>
bool Deque<T>::Front(T &value) const {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
        return false;
    }
    value = arr[front];
    return true;
}

template <class T>
bool Deque<T>::Rear(T &value) const {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
        return false;
    }
    value = arr[rear];
    return true;
}

template <class T>
void Deque<T>::Display() const {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    cout << "Current Deque: ";
    int i = front;
    while (true) {
        cout << arr[i] << " ";
        if (i == rear)
            break;
        i = (i + 1) % size;
    }
    cout << endl;
}
