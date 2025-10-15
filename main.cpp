/*
INSTRUCTIONS:
Fully comment each instruction in the code, explaining what's happening on that particular line. I want you to convince me that you understand what's happening with every pointer and line of code.

Additionally, write a class method every_other_element() that will output the data structure starting with the first element, skip the second element, output the third, skip fourth, etc. Demo this method in your code.
*/

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    // We use a struct to represent a single node in the linked list.
    struct Node {
        int data;       // Each node has data,
        Node* prev;     // a pointer to the previous node,
        Node* next;     // and a pointer to the next node.
        // Below is a Node constructor that initializes the members data, prev, and next.
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // head points to the first node of the linked list.
    Node* tail; // tail points to the last node of the linked list.

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }  // The default constructor for DoublyLinkedList sets the head and tail to nullptr.

    // This function inserts a new node after a given position.
    void insert_after(int value, int position) {    // The node node's data will be initialized to the value parameter.

        // Return if invalid negative position.
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // Create new node to be inserted.
        Node* newNode = new Node(value);

        // If the list is empty (head is nullptr), the new node becomes the head and the tail.
        if (!head) {
            head = tail = newNode;
            return;
        }
        
        // temp will be used to traverse the list.
        Node* temp = head;

        // Continue traversing the list until temp points to the correct position.
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;  // Point temp to the next node in the list

        if (!temp) {    // If temp ends up going past the list (temp is nullptr), return.
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Clean up the memory that was used up from the node we created earlier.
            return;
        }


        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}