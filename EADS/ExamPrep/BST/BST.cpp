#include <iostream>
#include <map>
#include <string>

using namespace std;

struct meaning
{
	int max;
	string type;
};

class BST
{
private:
    struct Node{
        int key;
        Node* left;
        Node* right;
    };
    Node* root;

    void destroy(Node*& p)
    {
        if (p != NULL)
        {
            destroy(p->left);
            destroy(p->right);
            delete p;
            p = NULL;
        }
    }

    void inOrder(Node*& p)
    {
        if (p!= NULL)
        {
            inOrder(p->left);
            cout << p->key << " ";
            inOrder(p->right);
        }
    }

    int height(Node* p) const
    {
        if (p == NULL)
        {
            return 0;
        }
        else
        {
            return 1 + max(height(p->left), height(p->right));
        }
    }

    	void findMaxHelper(int& oddLeaves, int& negativeNodes, int& parameterNodes, Node* p, const int& k)
	{
			if(p != NULL)
			{
				findMaxHelper(oddLeaves, negativeNodes, parameterNodes, p->left, k);
				if (!p->left && !p->right) //we have a leaf
				{
					if ((p->key % 2) == 1) //p is odd
					{
						oddLeaves++;
					}
				}
				else //not a leaf
				{
					if (p->key < 0)
					{
						negativeNodes++;
					}
					if (p->key > k)
					{
						parameterNodes++;
					}
				}
				findMaxHelper(oddLeaves, negativeNodes, parameterNodes, p->right, k);
			}
	}

public:
    BST(){
        root = NULL;
    }

    ~BST(){
        destroy(root);
    }
    void clear(){
        destroy(root);
    }

    void insert(const int& k){
        if (root == NULL)
        {
            root = new Node;
            root->key = k;
            root->left = NULL;
            root->right = NULL;
        }
        else
        {
            Node* current = root;
            Node* trailCurrent;
            while (current!= NULL)
            {
                trailCurrent = current;
                if (k < current->key)
                {
                    current = current->left;
                }
                else if (k > current->key)
                {
                    current = current->right;
                }
                else
                {
                    return;
                }
            }
            Node* newNode = new Node;
            newNode->key = k;
            newNode->left = NULL;
            newNode->right = NULL;
            if (k < trailCurrent->key)
            {
                trailCurrent->left = newNode;
            }
            else {
                trailCurrent->right = newNode;
            }
        }
    }

    void print(){
        inOrder(root);
    }
    int height(){
        return height(root);
    }
    bool isEmpty(){
        return root == NULL;
    }



	int findMax(int k, string& meaning)
	{
		int oddLeaves = 0;
		int negativeNodes = 0;
		int parameterNodes = 0;
		findMaxHelper(oddLeaves, negativeNodes, parameterNodes, root, k);
        int maximum = max(oddLeaves, max(negativeNodes, parameterNodes));
        if (maximum == oddLeaves)
        {
            meaning = "Leaves with keys of odd numbers";
        }
        else if (maximum == negativeNodes)
        {
            meaning = "Nodes with negative keys";
        }   
        else if (maximum == parameterNodes)
        {
            meaning = "Nodes with keys greater than parameter";
        }
        return maximum;
	}

};

int main()
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(1);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    bst.insert(9);
    bst.insert(10);
    bst.insert(11);


    string meaning;
    cout << bst.findMax(5, meaning) << meaning << endl;

    return 0;
    
}