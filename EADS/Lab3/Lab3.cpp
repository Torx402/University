//Lab3
//AVL binary search tree, quick access
//keys need to be unique
//
//testing of this dictionary, going to read a text, it will count how many words it will read
//keys will be any sequence of characters separated by a space
//it will count how many times a word has appeared, space, end of line, new line
//any ascii character with a space is a word
#include <iostream>
#include <exception>
using namespace std;

class keyNotFound: public exception
{
  virtual const char* what() const throw()
  {
    return "Key not found";
  }
} keyNotFound;

template <typename key, typename info>
class Dictionary { 
private:
    template <typename K, typename I>
    struct Node{
        K Key;
        I Info;
        Node* left;
        Node* right;
        int bfactor;
    };
    Node<key, info>* root;
    void copyTree(const Dictionary<key, info>* &copiedTree, const Dictionary<key, info>* otherTree)
    {
        if (otherTree == NULL)
        {
            copiedTree = NULL;
        }
        else
        {
            copiedTree = new Node;
            copiedTree->Key = otherTree->key;
            copiedTree->Info = otherTree->info;
            copyTree(copiedTree->left, otherTree->left);
            copyTree(copiedTree->right, otherTree->right);
        }
    }
    void destroy(Node<key, info>* d)
    {
        if (d != NULL)
        {
            destroy(d->left);
            destroy(d->right);
            delete d;
            d = NULL;
        }
    }
    void inorder(ostream& os, Node<key, info>* d) const
    {
        if (d != NULL)
        {
            inorder(os, d->left);
            cout << d->Key << ":" << d->Info << " ";
            inorder(os, d->right);
        }
    }
    int height(Node<key, info>* d)
    {
        if (d == NULL)
        {
            return 0;
        }
        else
        {
            return 1 + max(height(d->left), height(d->right));
        }
    }
    int max(int a, int b) const
    {
        return a > b? a : b;
    }

    void rotateToLeft(Node<key, info>* &d)
    {
        Node<key, info>* p;
        if (root == NULL)
        {
            return;
        }
        else if (root->right == NULL)
        {
            return;
        }
        else
        {
            p = root->right;
            root->right = p->left;
            p->left = root;
            root = p;
        }
    }
    void rotateToRight(Node<key, info>* &d)
    {
        Node<key, info>* p;
        if (root == NULL)
        {
            return;
        }
        else if (root->left == NULL)
        {
            return;
        }
        else
        {
            p = root->left;
            root->left = p->right;
            p->right = root;
            root = p;
        }
    }
    void balanceLeft(Node<key, info>* &d)
    {
        Node<key, info>* p;
        Node<key, info>* w;
        if (root == NULL)
        {
            return;
        }
        else if (root->left == NULL)
        {
            return;
        }
        else
        {
            p = d->left;
            switch(p->bfactor)
            {
                case -1:
                    d->bfactor = 0;
                    p->bfactor = 0;
                    rotateToRight(d);
                    break;
                case 0:
                    break;
                case 1:
                    w = p->right;
                    switch(w->bfactor)
                    {
                        case -1:
                            d->bfactor = 1;
                            p->bfactor = 0;
                            break;
                        case 0:
                            d->bfactor = 0;
                            p->bfactor = 0;
                            break;
                        case 1:
                            root->bfactor = 0;
                            p->bfactor = 1;
                    }
                    w->bfactor = 0;
                    rotateToLeft(p);
                    d->left = p;
                    rotateToRight(p);
            }
        }
    }
    void balanceRight(Node<key, info>* &d)
    {
        Node<key, info>* p;
        Node<key, info>* w;
        if (root == NULL)
        {
            return;
        }
        else if (root->right == NULL)
        {
            return;
        }
        else
        {
            p = d->right;
            switch(p->bfactor)
            {
                case 1:
                    d->bfactor = 0;
                    p->bfactor = 0;
                    rotateToLeft(d);
                    break;
                case 0:
                    break;
                case -1:
                    w = p->left;
                    switch(w->bfactor)
                    {
                        case 1:
                            d->bfactor = -1;
                            p->bfactor = 0;
                            break;
                        case 0:
                            d->bfactor = 0;
                            p->bfactor = 0;
                            break;
                        case -1:
                            root->bfactor = 0;
                            p->bfactor = -1;
                    }
                    w->bfactor = 0;
                    rotateToRight(p);
                    d->right = p;
                    rotateToLeft(p);
            }
        }
    }
    void insertIntoTree(Node<key, info>* &d, Node<key, info> *newNode, bool &isTaller)
    {
        if (d == NULL)
        {
            d = newNode;
            isTaller = true;
        }
        else if (newNode->Key == d->Key)
        {
            d->Info += newNode->Info;
            return;
        }
        else if (d->Key > newNode->Key)
        {
            insertIntoTree(d->left, newNode, isTaller);
            if (isTaller)
            {
                switch(d->bfactor)
                {
                    case -1:
                        balanceLeft(d);
                        isTaller = false;
                        break;
                    case 0:
                        d->bfactor = -1;
                        isTaller = true;
                        break;
                    case 1:
                        d->bfactor = 0;
                        isTaller = false;
                        break;
                }
            }
        }
        else
        {
            insertIntoTree(d->right, newNode, isTaller);
            if (isTaller)
            {
                switch(d->bfactor)
                {
                    case 1:
                        balanceRight(d);
                        isTaller = false;
                        break;
                    case 0:
                        d->bfactor = 1;
                        isTaller = true;
                        break;
                    case -1:
                        d->bfactor = 0;
                        isTaller = false;
                }
            }
        }
    }
    Node<key, info>* findNode(Node<key, info>* &d, key k) {
    // Base case: root is null or key is present at root
    if (d == nullptr || d->Key == k)
        return d;

    // Key is greater than root's key
    if (d->Key < k)
        return findNode(d->right, k);

    // Key is smaller than root's key
    return findNode(d->left, k);
}

public:
    Dictionary()
    {
        root = NULL;
    }
    ~Dictionary()
    {
        destroy(root);
    }
    Dictionary(const Dictionary<key, info>& d)
    {
        if (d.root == NULL)
        {
            root = NULL;
        }
        else
        {
            copyTree(root, d.root);
        }
    }
    const Dictionary<key, info>& operator=(const Dictionary<key, info>& d)
    {
        if (this != &d)
        {
            if (root != NULL)
            {
                destroy(root);
            }
            if (d.root == NULL)
            {
                root = NULL;
            }
            else
            {
                copyTree(root, d.root);
            }
        }
        return *this;
    }
    template <typename K, typename I>
    friend std::ostream& operator<<(std::ostream& os, const Dictionary<K, I>& dict);
    void print() const
    {
        inorder(root);
    }
    void clear()
    {
        destroy(root);
    }
    bool search(const key& k) const
    {
        if (root == NULL)
        {
            return false;
        }
        Node<key, info>* current = root;
        bool found = false;
        while (current != NULL && !found)
        {
            if (k == current->Key)
            {
                found = true;
            }
            else if (k < current->Key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return found;
    }

    info& operator[](const key& k)
    {
        Node<key, info>* current = findNode(root, k);
        if (current == NULL)
        {
            try
            {
                throw keyNotFound;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                exit(1);
            }
            
        }
        else { return current->Info; }
    }
    void insert(const key& k, const info& i)
    {
        bool isTaller = false;
        Node<key, info>* newNode = new Node<key, info>;
        newNode->Key = k;
        newNode->Info = i;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->bfactor = 0;
        insertIntoTree(root, newNode, isTaller);
    }
};

template <typename key, typename info>
std::ostream& operator<<(std::ostream& os, const Dictionary<key, info>& tree) {
    os << "{ ";
    tree.inorder(os, tree.root);
    os << "}";
    return os;
}