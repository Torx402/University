#ifndef RING_HPP
#define RING_HPP

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
    Node* last;
    int len;
public:
    Ring();
    ~Ring();
    const Ring<key, info>& operator=(const Ring<key, info>& other);
    class Itr
    {
    private:
        Node* current;
    public:
        Itr()
        {
            current = NULL;
        }
        Itr(const Ring<key, info>& ring)
        {
            current = ring.first;
        }
        const Itr& operator=(const Itr& other)
        {
            if (this != &other)
            {
                current = other.current;
            }
            return *this;
        }
        Itr& operator++()
        {
            current = current->Next;
            
            return *this;
        }
        Itr& operator--()
        {
            current = current->Prev;

            return *this;
        }
        info operator*()
        {
            return current->Info;
        }

        bool operator==(const Itr& other) const
        {
            return (current == other.current);
        }
        bool operator!=(const Itr& other) const
        {
            return (current != other.current);
        }

        friend class Ring;
    };
    bool isEmpty();
    void clear();
    int length();
    void search();
    void push(const key& k, const info& i);
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
    if (len == 1)
    {
        delete first;
        len--;
        return;
    }
    Node* curr = first;
    last = first->Prev;
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

    if (len == 0)
    {
        first = elem;
        first->Next = NULL;
        first->Prev = NULL;
        len++;
        return;
    }
    if (len == 1)
    {
        first = elem;
        ptr->Prev = elem;
        ptr->Next = elem;
        elem->Next = ptr;
        elem->Prev = ptr;
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




#endif