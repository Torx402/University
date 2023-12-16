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
   	Node *find(const key& k, int which = 1)
	{
		int count = 0;
		Node* current = first;

		if (!isEmpty()) //makes sure list isn't empty
		{
			while (count != which)
			{
				if (current->ki == k) //key = location specified by user
				{
					count++; //increase occurrance
					if (count == which) //check if which = occurrance
					{
						return current;
					}
					else if (current->Next != NULL && current->Next != first)
					{
						current = current->Next;
					}
				}
				else if (current->Next != NULL)
				{
					current = current->Next;
				}
				else
				{ 
				return NULL;
				}
			}
		}
		return NULL;
		//finds element and returns its address
	}
public:
    Ring();
    ~Ring();
    const Ring<key, info>& operator=(const Ring<key, info>& other);
    template <typename K, typename I>
    class Itr
    {
    private:
        Node* current;
        const Ring<key, info>* ring; //keeps in mind which ring it is working on
    public:
        Itr()
        {
            current = NULL;
            ring = NULL;
        }
        Itr(const Ring<key, info>& Ring)
        {
            current = Ring.first;
            ring = &Ring;
        }
        const Itr& operator=(const Itr& Other)
        {
            if (this != &Other)
            {
                current = Other.current;
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
            current = current->Prev;

            return *this;
        }
        I& operator*()
        {
            assert(current != NULL);
            return current->Info;
        }
        void begin()
        {
            assert(ring && !ring->isEmpty());
            current = ring->First;
        }
        void end()
        {
            assert(ring && !ring->IsEmpty());
            current = ring->Prev;
        }

        K& Key()
        {
            assert(current);
            return current->Key;
        }

        bool operator==(const Itr& Other) const
        {
            return (current == Other.current);
        }
        bool operator!=(const Itr& Other) const
        {
            return (current != Other.current);
        }

        friend class Ring;
    };
    typedef Itr<key, info> Iter;
    bool isEmpty();
    void clear();
    int length() {return len;}
    void push(const key& k, const info& i);
    bool remove(const Itr<key, info>& itr);
    bool search(Itr<key, info>& itr ,const info& I, int which = 1);
    bool insertAfter(const key& What, const info& iWhat, const Itr<key, info>& itr, int which = 1);

};

template <typename key, typename info>
Ring<key, info>::Ring()
{
    first = NULL;
    len = 0;
}

template <typename key, typename info>
Ring<key, info>::~Ring()
{
    clear();
}

template <typename key, typename info>
bool Ring<key, info>::isEmpty()
{
    return (len == 0);
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
void Ring<key, info>::push(const key& k, const info& i)
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
        return;
    }

    prev = first->Prev;
    first = elem;
    elem->Prev = prev;
    elem->Next = ptr;
    ptr->Prev = first;
    prev->Next = first;
    len++;
}

template <typename key, typename info>
bool Ring<key, info>::search(Itr<key, info>& itr,const info& I, int which)
{
    assertitr.ring
    if (isEmpty())
    {
        return false;
    }
    int count = 0;
    if (first == I)
    {
        count++;
        if (count == which)
        {
            return true;
        }
    }
    ++itr;
    
    while(itr != first)
    {
        if(*itr == I)
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