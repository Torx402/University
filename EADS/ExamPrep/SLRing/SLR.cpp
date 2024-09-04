#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* next;

    Node(int key) {
        this->key = key;
        this->next = nullptr;
    }
};

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList() {
        head = nullptr;
    }

    // Method to insert a node at the end of the ring
    void insert(int key) {
        Node* newNode = new Node(key);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    // Method to remove a node by key
    bool remove(int key) {
        if (head == nullptr) return false;

        Node* temp = head;
        Node* prev = nullptr;

        // If head needs to be removed
        if (temp->key == key) {
            if(temp->next == head) {
                delete temp;
                head = nullptr;
                return true;
            }

            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }

            head = head->next;
            last->next = head;
            delete temp;
            return true;
        }

        // Find the node to be deleted
        do {
            prev = temp;
            temp = temp->next;
            if (temp->key == key) {
                prev->next = temp->next;
                delete temp;
                return true;
            }
        } while (temp != head);

        return false;
    }

    // Overloading the stream insertion operator
    friend ostream& operator<<(ostream& os, const CircularLinkedList& list) {
        if (list.head == nullptr) {
            os << "List is empty.";
            return os;
        }

        Node* temp = list.head;
        do {
            os << temp->key << " ";
            temp = temp->next;
        } while (temp != list.head);

        return os;
    }
};

int main() {
    CircularLinkedList myList;
    myList.insert(1);
    myList.insert(2);
    myList.insert(3);

    cout << "List after insertion: " << myList << endl;

    myList.remove(2);

    cout << "List after removal: " << myList << endl;

    return 0;
}
