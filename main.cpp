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
        
        // temp pointer will be used to traverse the list.
        Node* temp = head;

        // Continue traversing the list until either temp points to the correct position, or temp becomes nullptr (temp has gone past the list).
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;  // Point temp to the next node in the list

        if (!temp) {    // If temp ends up going past the list (temp is nullptr), return.
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Clean up the memory that was used up from the node we created earlier but never inserted.
            return;
        }
        
        // Wire the next and prev pointers of the new node we created before we insert it into the list.
        newNode->next = temp->next;     // newNode's next points to the node after temp.
        newNode->prev = temp;           // newNode's prev points to temp (because it will be inserted after temp).

        if (temp->next)                 // If we are NOT inserting at the tail (meaning a node to the right exists),
            temp->next->prev = newNode; // rewire the node to the right's prev to point at newNode.
        else                            // Else if we ARE inserting at the tail,
            tail = newNode;             // the tail of the linked list becomes our new node.
        temp->next = newNode;           // Finally, temp's next points to our newNode (because newNode is inserted after temp).
    }

    // This function will delete the first node in the linked list that contains the given value.
    void delete_val(int value) {
        if (!head) return;  // If the list is empty, return.

        Node* temp = head;  // temp pointer will be used to traverse the list.
        
        // Traverse the list until we find a node with the value or until temp becomes nullptr (temp has gone past the list).
        while (temp && temp->data != value)
            temp = temp->next;  // Point temp to the next node in the list

        if (!temp) return; // If temp is nullptr (meaning it has gone past the list), return because we didn't find any node with the value.

        // Now we will rewire the nodes surrounding the node we want to delete so that the linked list remains intact.
        if (temp->prev)                         // If we are NOT deleting the head (meaning that a node to the left exists),
            temp->prev->next = temp->next;      // rewire the node to the left's next to point at the node AFTER the one we're going to delete.
        else                                    // Else if we ARE deleting the head,
            head = temp->next;                  // the head of the linked list is rewired to point to the node AFTER the one we're going to delete.

        if (temp->next)                         // If we are NOT deleting the tail (meaning that a node to the right exists),
            temp->next->prev = temp->prev;      // rewire hte node to the right's prev to point at the node BEFORE the one we're going to delete.
        else                                    // Else if we ARE deleting the tail,
            tail = temp->prev;                  // the tail of the linked list is rewired to point to the node BEFORE the one we're going to delete.

        delete temp;    // Finally, delete the node by freeing its memory.
    }

    // This function will delete the node at a given position.
    void delete_pos(int pos) {

        // If the list is empty (head is nullptr), return.
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {     // If the head is being deleted,
            pop_front();    // simply call pop_front and return.
            return;
        }
    
        // temp pointer will be used to traverse the list.
        Node* temp = head;
    
        // The for loop will traverse the loop up to the given position.
        for (int i = 1; i < pos; i++){
            if (!temp) {    // Each iteration checks that temp is not nullptr. If temp IS nullptr, it has gone past the list (invalid position).
                cout << "Position doesn't exist." << endl;
                return;     // Return due to invalid position.
            }
            else
                temp = temp->next;  // Point temp to the next node in the list.
        }

        // Check if the final position is valid, meaning temp is not nullptr.
        if (!temp) {    // If temp IS nullptr, it has gone past the list (invalid position), so return.
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {  // If we are deleting the TAIL (meaning that no node to the right exists),
            pop_back();     // simply call pop_back() and return.
            return;
        }
    
        // Now we will rewire the nodes surrounding the node we want to delete so that the linked list remains intact.
        Node* tempPrev = temp->prev;    // Point to the node to the left of the one we want to delete.
        tempPrev->next = temp->next;    // The node to the left's next will point to the node AFTER the one to be deleted.
        temp->next->prev = tempPrev;    // The node to the right of the one we want to delete will now have its prev point to the node BEFORE the one we want to delete.

        delete temp;    // Finally, delete the node by freeing its memory.
    }

    // This function will add a new node to the end of the linked list, initialized with the parameter v.
    void push_back(int v) {
        Node* newNode = new Node(v);    // Create a new node using v to initialize its data.
        if (!tail)                      // If the list is empty,
            head = tail = newNode;      // the new node becomes the list's head and tail.
        else {                          // Else if the list is not empty,
            tail->next = newNode;       // the old tail's next will point to the new node
            newNode->prev = tail;       // and the new node's prev will point to the old tail.
            tail = newNode;             // Finally, the tail of the list becomes the new node we inserted.
        }
    }
    
    // This function will add a new node to the front of the linked list, initialized with the parameter v.
    void push_front(int v) {
        Node* newNode = new Node(v);    // Create a new node using v to initialize its data.
        if (!head)                      // If the list is empty,
            head = tail = newNode;      // the node node becomes the list's head and tail.
        else {                          // Else if the list is not empty,
            newNode->next = head;       // the new node's next will point to the old head,
            head->prev = newNode;       // and the old head's prev will point to the new node.
            head = newNode;             // Finally, the head of the list becomes the new node we inserted.
        }
    }
    
    // This function will delete the node at the front of the linked list.
    void pop_front() {

        if (!head) {    // If the list is empty, return because there's nothing to delete.
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; // temp will temporarily point to the node we're going to delete (the head).

        if (head->next) {           // If a node exists after the current head,
            head = head->next;      // the node after the current head will become the new head of the list,
            head->prev = nullptr;   // and the new head's prev will be nullptr.
        }
        else                        // Else if a node doesn't exist after the head (meaning there's only one node in the list),
            head = tail = nullptr;  // both the head and tail become nullptr and the list is empty.

        delete temp;    // Finally, delete the original head by freeing its memory.
    }

    // This function will delete the last node in the linked list.
    void pop_back() {

        if (!tail) {    // If the list is empty, return because there's nothing to delete.
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = tail; // temp will temporarily point to the node we're going to delete (the tail).

        if (tail->prev) {           // If a node exists before the current tail,
            tail = tail->prev;      // the node before the current tail will become the new tail of the list,
            tail->next = nullptr;   // and the new tail's prev will be nullptr.
        }
        else                        // Else if a node doesn't exist before the tail (meaning there's only one node in the list),
            head = tail = nullptr;  // both the head and tail become nullptr and the list is empty.

        delete temp;    // Finally, delete the original tail by freeing its memory.
    }

    // This is the destructor for the DoublyLinkedList.
    // It ensures that the memory of each node is properly freed when a DoublyLinkedList object goes out of scope.
    ~DoublyLinkedList() {
        while (head) {          // Go through the list as long as nodes exist
            Node* temp = head;  // Point to the current, old head
            head = head->next;  // Move head to point to the next node. (head will become nullptr once it reaches the end of the list, which will end the traversal loop.)
            delete temp;        // Delete the 'old head'
        }
    }

    // This function will print each node's data in the linked list.
    void print() {
        Node* current = head;   // current will be used to traverse the node, beginning at the head
        if (!current) { // Return if empty list (meaning head is nullptr).
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // While current is not nullptr (meaning it is within the linked list),
            cout << current->data << " ";   // print the data of the current node
            current = current->next;        // point current to the next node, until it points to nullptr (which will end the traversal loop)
        }
        cout << endl;
    }

    // This function will print each node's data in the linked list, but in reverse, from tail to head.
    void print_reverse() {
        Node* current = tail;   // current will be used to traverse the node, beginning at the tail
        if (!current) {         // Return if empty is list (meaning that tail is nullptr)
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // While current is not nullptr (meaning it is within the linked list),
            cout << current->data << " ";   // print the data of the current node
            current = current->prev;        // point current to the previous node, until it points to nullptr (which will end the traversal loop)
        }
        cout << endl;
    }

    // This function will print every other element in the list.
    void every_other_element() {
        Node* current = head;   // current will be used to traverse the node, beginning at the head
        if (!current) { // Return if empty list (meaning head is nullptr).
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // While current is not nullptr (meaning it is within the linked list),
            cout << current->data << " ";             // print the data of the current node
            if (current->next) {                      // If a node exists to the right,
                current = current->next->next;        // point current to the NEXT NEXT node, skipping the one in between.
                                                      // (If we assigned current to current->next->next without checking if a node to the right exists,
                                                      // we might dangerously point current to some random data past the linked list.)
                                                      // (By checking that current->next exists,
                                                      // we ensure that current is ONLY ever assigned to either: a node, or nullptr
            }
            else {                  // If no node to the right exists,
                current = nullptr;  // End the loop by assigning current nullptr (because the loop only continues when current is not nullptr).
            }
        }
        cout << endl;
    }
};

int main() {
    // cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList list;
    for (int i = 0; i < 10; ++i) {  // linked list will contain nodes with values 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        list.push_back(i);
    }

    list.every_other_element();     // print out every other element: 0, 2, 4, 6, 8

    
    return 0;
}