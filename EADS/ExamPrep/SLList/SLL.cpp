#include <iostream>

using namespace std;

class SLL
{
private:
    struct Node
    {
        int key;
        Node *next;
    };
    Node *head;
    Node *last;

    void removeNext(Node*& current)
	{
		//if head is to be removed
		if (current == head)
		{
			//if head is the only node in the list
			if (current->next == NULL)
			{
				delete current;
				head = NULL;
				return;
			}
			else //if head is the last odd element in the list 
			{
				head = current->next;
				delete current;
				return;
			}
		}
		Node* p = current;
		current = current->next;
		if (current->next == NULL) //Node to be deleted is last node in list
		{
			delete current;
			p->next = NULL;
		}
		else 
		{
			Node* q = current->next;
			delete current;
			p->next = q;
		} 
	}

    void removeLastOdd() {
    if (!head) { return; }
    Node* current = head;
    Node* LastOdd = NULL;
    if ((head->key % 2) == 1)
    {
        LastOdd = head;
        //head is the only node in the list
        if (head->next == NULL)
        {
            removeNext(LastOdd);
            return;
        }
    }
    while (current->next->next != NULL)
    {
        if ((current->next->key % 2) == 1)
        {
            LastOdd = current;
        }
        current = current->next;
    }
    //Processing last node
    if ((current->next->key % 2) == 1)
    {
        LastOdd = current;
    }
    removeNext(LastOdd);
	}
public:
    SLL(){ head = NULL; }
    ~SLL() { clear(); }

    void print() const {
        Node* current = head;
        while (current != NULL) {
            cout << current->key << " ";
            current = current->next;
        }
        cout << endl;
    }

    void clear() {
        Node *temp = NULL;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
        last = NULL;
    }

    void pushBack(const int& k) {
        Node *newNode = new Node;
        newNode->key = k;
        newNode->next = NULL;
        if (head == NULL)
        {
            head = newNode;
            last = newNode;
        }
        else
        {
            last->next = newNode;
            last = newNode;
        }
    }
    void removeLastNOdd(int n){
		if (n > 0){
			removeLastNOdd(n-2);
		}
		removeLastOdd();
	}
};

int main()
{
    SLL list;
    list.pushBack(1);
    list.print();
    list.removeLastNOdd(2);
    list.print();
}