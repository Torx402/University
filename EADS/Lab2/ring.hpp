#ifndef RING_HPP
#define RING_HPP
#include <iostream>
#include <cassert>
template<typename key, typename info>
class Ring
{
private:
    struct Node
    {
        key Key;
        info Info;
        Node* Next;
        Node* Prev;
    };
    Node* first;
    int len;
public:
    Ring();
    Ring(const Ring<key, info>& Other);
    ~Ring() { clear(); }
    void copyRing(const Ring<key, info>& Other);
    const Ring<key, info>& operator=(const Ring<key, info>& Other)
    {
        if (this != &Other)
        {
            copyRing(Other);
        }
        return *this;
    }
    template <typename K, typename I>
    class Itr
    {
    private:
        Node* current;
        Ring<key, info>* ring; //keeps in mind which ring it is working on
        void copyItr(const Itr& Other)
        {
            current = Other.current;
            ring = Other.ring;
        }
    public:
        Itr()
        {
            current = NULL;
            ring = NULL;
        }
        Itr(Ring<key, info>& Ring)
        {
            current = Ring.first;
            ring = &Ring;
        }
        const Itr& operator=(const Itr& Other)
        {
            if (this != &Other)
            {
                copyItr(Other);
            }
            return *this;
        }
        Itr& operator++()
        {
            assert(current->Next);
            current = current->Next;
            
            return *this;
        }
        Itr& operator--()
        {
            assert(current->Prev);
            current = current->Prev;

            return *this;
        }
        const I& operator*() const
        {
            assert(current != NULL);
            return current->Info;
        }
        void begin()
        {
            assert(ring && !ring->isEmpty());
            current = ring->first;
        }

        const K& Key() const
        {
            assert(current);
            return current->Key;
        }
        
        Itr& goTo(const info& iWhat, int which = 1)
        {
            assert(ring);
            Itr temp = *this;
            int count = 0;
            if (**this == iWhat)
            {
                count++;
                if (count == which)
                {
                    return *this;
                }
            }
            ++(*this);
            
            while(this->current != ring->first)
            {
                if(**this == iWhat)
                {
                    count++;
                }
                if(count == which)
                {
                    return *this;
                }
                else ++(*this);
            }
            return temp;
        }
        void remove()
        {
            
        }

        bool operator==(const Itr& Other) const { return (current == Other.current); }
        bool operator!=(const Itr& Other) const { return (current != Other.current); }

        friend class Ring;
    };
    typedef Itr<key, info> Iter;
    bool isEmpty() { return (len == 0); }
    void clear();
    int length() {return len;}
    bool push(const key& k, const info& i);
    bool pop();
    bool remove(const Itr<key, info>& itr);
    bool search(Itr<key, info>& itr ,const key& what, const info& iWhat, int which = 1);
    bool insertAfter(const key& What, const info& iWhat, int which = 1);
    bool insertBefore(Itr<key, info>& itr ,const key& What, const info& iWhat, int which = 1);
};

template <typename key, typename info>
Ring<key, info>::Ring()
{
    first = NULL;
    len = 0;
}

template <typename key, typename info>
Ring<key, info>::Ring(const Ring<key, info>& Other)
{
    first = NULL;
    copyRing(Other);
}

template <typename key, typename info>
void Ring<key, info>::copyRing(const Ring<key, info>& Other)
{
    Node* newNode;
    Node* current;
    Node* last;
    Node* q;
    if (first != NULL)
    {
        clear();
    }

    if (Other.first == NULL)
    {
        first = NULL;
        len = 0;
    }
    else
    {
        current = Other.first;
        last = current->Prev;

        len = Other.len;
        //First Node
        first = new Node;
        first->Key = current->Key;
        first->Info = current->Info;
        first->Next = first;
        first->Prev = first;
        q = first;

        current = current->Next;
        //Other nodes
        while (current != Other.first)
        {
            newNode = new Node;
            newNode->Info = current->Info;
            newNode->Key = current->Key;
            newNode->Next = first;
            newNode->Prev = q;
            q->Next = newNode;
            first->Prev = newNode;
            q = newNode;
            current = current->Next;
        }
    }
}

template <typename key, typename info>
void Ring<key, info>::clear()
{
    if (isEmpty())
    {
        return;
    }
    Node* curr = first;
    Node* last = first->Prev;
    while (curr != last)
    {
        first = first->Next;
        last->Next = first;
        first->Prev = last;
        delete curr;
        curr = first;
        len--;
    }
    if (curr)
    {
        delete curr;
        len--;
    }
}

template <typename key, typename info>
bool Ring<key, info>::push(const key& k, const info& i)
{
    Node* ptr = first;
    Node* prev = new Node;
    Node *elem = new Node;
    elem->Info = i;
    elem->Key = k;

    if (isEmpty())
    {
        first = elem;
        first->Next = first;
        first->Prev = first;
        len++;
        return true;
    }
    else
    {
        prev = first->Prev;
        first = elem;
        elem->Prev = prev;
        elem->Next = ptr;
        ptr->Prev = first;
        prev->Next = first;
        len++;
        return true;
    }
    return false;
}
template <typename key, typename info>
bool Ring<key, info>::pop()
{

}
template <typename key, typename info>
bool Ring<key, info>::search(Itr<key, info>& itr, const key& what, const info& iWhat, int which)
{
    assert(itr.ring == this);
    if (isEmpty())
    {
        return false;
    }
    int count = 0;
    if (*itr == iWhat && itr.Key() == what)
    {
        count++;
        if (count == which)
        {
            return true;
        }
    }
    ++itr;
    
    while(itr.current != first)
    {
        if(*itr == iWhat && itr.Key() == what)
        {
            count++;
        }
        if(count == which)
        {
            return true;
        }
        else ++itr;
    }
    return false;
}





#endif