#include <iostream>
#include "task3.cpp"
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;

    void PrintForwardRec(Node* node) const;
    void PrintReverseRec(Node* node) const;

public:
    SinglyLinkedList();
    void InsertAtEnd(int val);
    void PrintForward() const;
    void PrintReverse() const;
    Node* GetHead() const;
    void SetHead(Node* h);
    Node* MergeRec(Node* list1, Node* list2);
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    bool RecursivePalindromeCheck(Node* left, Node* right);
public:
    DoublyLinkedList();
    void InsertAtEnd(int val);
    void Display();
    bool isPalindrome();
};

int main() {
    // ============================= Singly Linked List Demo =============================
    cout << "=== Singly Linked List Demo ===" << endl;
    SinglyLinkedList list;
    int n, val;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter values ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        list.InsertAtEnd(val);
    }

    list.PrintForward();
    list.PrintReverse();


    // ============================ Deque Recursive Search Demo =============================
    cout << endl << endl <<"=== Deque Recursive Search Demo ===" << endl;

    Deque<int> dq(10);
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter values ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        dq.EnqueueAtRear(val);
    }
    dq.Display();

    int searchValue;
    cout << "Enter value to search: ";
    cin >> searchValue;
    int index = dq.RecursiveSearch(searchValue);
    if (index != -1) {
        cout << "Value " << searchValue << " found at index " << index << "." << endl;
    } else {
        cout << "Value " << searchValue << " not found in the deque." << endl;
    }


    // ============================ Doubly Linked List Palindrome Check Demo =============================
    cout << endl << endl <<"=== Doubly Linked List Palindrome Check Demo ===" << endl;
    DoublyLinkedList dlist;
    cout << "Enter number of elements for Doubly Linked List: ";
    cin >> n;
    cout << "Enter values: ";
    for (int i = 0; i < n; i++) {  
        cin >> val;
        dlist.InsertAtEnd(val);
    }
    dlist.Display();
    if (dlist.isPalindrome()) {
        cout << "The doubly linked list is a palindrome." << endl;
    } else {
        cout << "The doubly linked list is not a palindrome." << endl;
    } 

    // ============================ Merge Two Sorted Singly Linked Lists Demo =============================
    cout << endl << endl <<"=== Merge Two Sorted Singly Linked Lists Demo ===" << endl;
    SinglyLinkedList list1, list2;
    int n1, n2;
    cout << "Enter number of elements for first sorted list: ";
    cin >> n1;
    cout << "Enter values in sorted order: ";
    for (int i = 0; i < n1; i++) {
        cin >> val;
        list1.InsertAtEnd(val);
    }
    cout << "Enter number of elements for second sorted list: ";
    cin >> n2;
    cout << "Enter values in sorted order: ";
    for (int i = 0; i < n2; i++) {
        cin >> val;
        list2.InsertAtEnd(val);
    }
    Node* mergedHead = list1.MergeRec(list1.GetHead(), list2.GetHead());
    SinglyLinkedList mergedList;
    mergedList.SetHead(mergedHead);
    cout << "Merged Sorted List: ";
    mergedList.PrintForward();

    return 0;
}

//========================= Singly Linked List Implementation ======================

SinglyLinkedList::SinglyLinkedList() {
    head = nullptr;
}

void SinglyLinkedList::InsertAtEnd(int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

void SinglyLinkedList::PrintForwardRec(Node* node) const {
    if (!node) return;
    cout << node->data << " ";
    PrintForwardRec(node->next);
}

void SinglyLinkedList::PrintReverseRec(Node* node) const {
    if (!node) return;
    PrintReverseRec(node->next);
    cout << node->data << " ";
}

void SinglyLinkedList::PrintForward() const {
    cout << "List (Forward): ";
    PrintForwardRec(head);
    cout << endl;
}

void SinglyLinkedList::PrintReverse() const {
    cout << "List (Reverse): ";
    PrintReverseRec(head);
    cout << endl;
}

//========================= Recursive search implementation for Deque======================

template <class T>
int Deque<T>::RecursiveSearch(T& value, int index) {
    if (isEmpty()) {
        return -1; // Deque is empty
    }
    if (index >= size) {
        return -1; // Reached end without finding
    }
    if(arr[index] == value) {
        return index; // Found the value
    }
    return RecursiveSearch(value, index + 1); 
}

//========================= Doubly Linked List Implementation ======================
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}
void DoublyLinkedList::InsertAtEnd(int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}
void DoublyLinkedList::Display() {
    Node* temp = head;
    cout << "Doubly Linked List: ";
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

bool DoublyLinkedList::isPalindrome() {
    if(!head) return true; // Empty list is palindrome
    return RecursivePalindromeCheck(head, tail);
}

bool DoublyLinkedList::RecursivePalindromeCheck(Node* left, Node* right) {
    if (left == nullptr || right == nullptr) return true;
    if (left->data != right->data) return false;
    if (left == right || left->prev == right) return true; // Base case
    
    return RecursivePalindromeCheck(left->next, right->prev);
}

// ===================Recursive Merge of two Sorted Singly Linked Lists===================
Node* SinglyLinkedList::GetHead() const {
    return head;
}

void SinglyLinkedList::SetHead(Node* h) {
    head = h;
}

Node* SinglyLinkedList::MergeRec(Node* list1, Node* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    if (list1->data <= list2->data) {
        list1->next = MergeRec(list1->next, list2);
        return list1;
    } else {
        list2->next = MergeRec(list1, list2->next);
        return list2;
    }
}