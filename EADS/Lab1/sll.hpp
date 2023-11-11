#ifndef H_SLL
#define H_SLL
#include <iostream>

//EADS LAB 1
//Task is to design and implement this class, iterator can be added, but not recommended, it is a source of errors
template<typename key, typename info>
class Sequence { //implemented using single linked list
//non-negotiables
//methods should not use index as a way to identify a given element, so element should be identified using keys
public:
	Sequence();
	~Sequence();
	bool insertAfter(const key& What, const info& iWhat, const key& where, int which = 1);
	void pushFront(const key& k, const info& i);
	void pushBack(const key& k, const info& i);
	bool remove(const key& k, int which = 1);
	bool popFront();
	bool popBack();
	//it is important to highlight the value of the idea here, these methods can work regardless of the data structure we decide to choose
	//implementation is secondary.
	//another way to implement front is as follows
	bool front(info& i) const;
	bool back(info& i) const;
	bool getinfo(info& i, const key& k, int which = 1);
	int length() const;
	bool isempty() const;
	void clear();
	bool search(const key& k, int which = 1);
	friend std::ostream& operator<<(std::ostream& o, const Sequence<key, info>& s)
	{
		Node *curr = s.first;
		if (curr != NULL)
		{
			do
			{
				o << "(" << curr->ki << ", " << curr->inf << ")";
				curr = curr->next;
			} while (curr);
			
		}
		else
		{
			o << "List is empty!";
		}
		return o;
	}
	void reverse();
	void swap(Sequence<key, info>& s);
	void split(Sequence<key, info>& result1, int len1, int repeat1,
			Sequence<key, info>& result2, int len2, int repeat2);
	//Sequence<key, info> subSequence (const key& startK, int startCh, const key& endK, int endCh);
	// this will allow us to create subsequences given the arguments above, we may overload the arguments to have different options when creating
	// a subsequence
private:
	struct Node
	{
		key ki;
		info inf;
		Node *next;
	};
	Node *first; //first element in the sequence (head, front)
	Node *last;	//last element in the list (end)
	Node *current;
	int len; //length of the sequence
	Node *find(const key& k, int which = 1)
	{
		int count = 0;
		current = first;
		if (!isempty()) //makes sure list isn't empty
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
					else if (current->next != NULL)
					{
						current = current->next;
					}
				}
				else if (current->next != NULL)
				{
					current = current->next;
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
};

//external function that checks proper implementation of the class, its flexibility per se, this is an external function ofc, not friend or method
//the main idea however, involves the proper design of the class, that's where the focus is, the focus shouldn't be to just implement a class that satisfies the implmenetation of source
template <typename key, typename info>
//splits the sequence into two results
void Sequence<key, info>::split(Sequence<key, info>& result1, int len1, int repeat1,
			Sequence<key, info>& result2, int len2, int repeat2)
{
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
	}
	current = first;
	int r1 = 0;
	int r2 = 0;
	int l1, l2;
	while(r1 != repeat1 || r2 != repeat2) //this makes sure it keeps running as long as r1 or 
	{
		if (r1 != repeat1)
		{
			l1 = 0;
		}
		while(l1 != len1)
		{
			if(current)
			{
				result1.pushBack(current->ki, current->inf);
				l1++;
				if (current->next != NULL)
				{
					current = current->next;
				}
				else
				{
					return;
				}
			}
			//copies len1 items to result1
		}
		if (l1 == len1)
		{
			r1++;
		}
		if (r2 != repeat2)
		{
			l2 = 0;
		}
		while(l2 != len2)
		{
			if (current)
			{
				result2.pushBack(current->ki, current->inf);
				l2++;
				if (current->next != NULL)
				{
					current = current->next;
				}
				else
				{
					return;
				}
			}
			//copies len2 items to result2
		} 
		if (l2 == len2)
		{
			r2++;
		}
	}
}
//th function splits the sequence, it starts at the beginning 
//tests are very much appreciated

template <typename key, typename info>
Sequence<key, info>::Sequence()
{
	first = NULL;
	last = NULL;
	len = 0;
}

template <typename key, typename info>
Sequence<key, info>::~Sequence()
{
	clear();
	//destructor, makes sure memory leaks won't happen
}

template <typename key, typename info>
bool Sequence<key, info>::insertAfter(const key& What, const info& iWhat, const key& where, int which)
{
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	current = find(where, which);
	if (current == NULL)
	{
		std::cout << "Element does not exist!" << std::endl;
		return false;
	}
	if(current == first)
	{
		pushFront(What, iWhat);
		return true;
	}
	else if (current == last)
	{
		pushBack(What, iWhat);
		return true;
	}

	Node *p = current->next;
	Node *elem = new Node;
	elem->ki = What;
	elem->inf = iWhat;
	elem->next = p;
	current->next = elem;
	len++;
	return true;
	//inserts a node after the <which> occurrance of a specific key
	//returns true if successful, increments length, false in case <where> cannot be found
}

template <typename key, typename info>
void Sequence<key, info>::pushFront(const key& k, const info& i)
{
	Node *elem = new Node;
	elem->ki = k;
	elem->inf = i;
	elem->next = NULL;
	if (len == 0)
	{
		first = elem;
		last = elem;
		len++;
	}
	else
	{
		elem->next = first;
		first = elem;
		len++;
	}

	
	//inserts an element at the front of the list (inserted element becomes first element)
	//list must exist
	//different case when inserted element is first element to be inserted or otherwise
	//increments length
	//should report error in case element cannot be pushed
}

template <typename key, typename info>
void Sequence<key, info>::pushBack(const key& k, const info& i)
{
	current = last;
	Node *elem = new Node;
	elem->ki = k;
	elem->inf = i;
	elem->next = NULL;
	if (len == 0)
	{
		first = elem;
		last = elem;
		len++;
	}
	else
	{
		current->next = elem;
		last = elem;
		len++;
	}

	//inserts an element at the end of the list
	//inserted element becomes last element
	//list must exist
	//different cases when element is the first element to be added or otherwise
	//increments length
	//should report error in case element cannot be pushed
}

template <typename key, typename info>
bool Sequence<key, info>::remove(const key& k, int which)
{
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	Node *p = first;
	current = find(k, which);
	if (current == NULL)
	{
		std::cout << "Element does not exist!" << std::endl;
		return false;
	}
	if (len == 1)
	{
		popFront();
		return true;
	}
	Node *q = current->next;
	while (p->next != current)
	{
		p = p->next;
	}
	if (current == last)
	{
		popBack();
		return true;
	}
	p->next = q;
	delete current;
	len--;
	return true;
	
	//list must not be empty
	//removes an element with <which> occurance given a key
	//returns true if successful, decrement length
	//returns false if key cannot be found, or which is invalid
}

template <typename key, typename info>
bool Sequence<key, info>::popFront()
{
	if(isempty())
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	//must consider separate cases for when there is 1 element or more in the list
	current = first;
	if(len == 1)
	{
		first = NULL;
		last = NULL;
		delete current;
		len--;
		return true;
	}
	else
	{
		first = current->next;
		delete current;
		len--;
		return true;
	}
	
	//removes first element, list must have at least one element
	//returns true if successfully removes the element, decrement length
	//list must exist and have at least one element
	//returns false if popping fails
}

template <typename key, typename info>
bool Sequence<key, info>::popBack() //standard stl approach involves popping and forgetting, not returning the element
{
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	current = last;
	if (len == 1)
	{
		first = NULL;
		last = NULL;
		delete current;
		len--;
		return true;
	}
	else
	{
		Node *p = first;
		while (p->next != last)
		{
			p = p->next;
		}
		p->next = NULL;
		last = p;
		delete current;
		len--;
		return true;
	}

	//removes element at the end of the list
	//list must exist and contain at least one element
	//returns true if successful, decrement length
	//returns false otherwise
}
//it is important to highlight the value of the idea here, these methods can work regardless of the data structure we decide to choose
//implementation is secondary.
//another way to implement front is as follows
template <typename key, typename info>
bool Sequence<key, info>::front(info& i) const //if true, value will be info of first element (passed as reference), also possible to add key reference
{
	if (first != NULL)
	{
		i = first->inf;
		return true;
	}
	else
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	//list must exist and contain at least one element
	//assigns info section of first element to provided argument
	//returns true if successful, false if list is empty
}

template <typename key, typename info>
bool Sequence<key, info>::back(info& i) const
{	
	//test combining with || last == NULL
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	if (last != NULL)
	{
		i = last->inf;
		return true;
	}
	else
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	//same as above, but for last element
}

template <typename key, typename info>
bool Sequence<key, info>::getinfo(info& i, const key& k, int which) //name of these arguments isnt necessary becuase they are rather distinct, it is up to you
{
	//TODO
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	current = find(k, which);
	if (current == NULL)
	{
		std::cout << "Element does not exist!" << std::endl;
		return false;
	}
	else
	{
		i = current->inf;
		return true;
	}
	//assigns info of an element with specified key and occurrance to info argument
	//returns true if successful
	//returns false if list is empty, or element with such key or occurrence cannot be found (think about returning nearest element to which if which itself doesn't exist)
}

template <typename key, typename info>
int Sequence<key, info>::length() const
{
	return len;
	//returns list length
}

template <typename key, typename info>
bool Sequence<key, info>::isempty() const
{
	if (len == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	//returns true if list is empty, false otherwise
}

template <typename key, typename info>
void Sequence<key, info>::clear()
{
	Node *temp = NULL;
	while (first != NULL)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
	last = NULL;
	len = 0;
	//empties the list
	//be careful of memory!
}

template <typename key, typename info>
bool Sequence<key, info>::search(const key& k, int which)
{
	Node* temp = find(k, which);
	if (temp)
	return true;
	else
	return false;
	//finds element and returns its address
}

template <typename key, typename info>
void Sequence<key, info>::reverse()
{
	if (isempty())
	{
		std::cout << "List is empty!" << std::endl;
	}
	else
	{
		Node* p = NULL;
		current = first;
		Node* q = NULL;
		while (current != NULL)
		{
			q = current->next;
			current->next = p;
			if (current->next == NULL)
			{
				last = current;
			}
			p = current;
			current = q;
			
		}
		first = p;
	}
	
	//reverses the list
}

template <typename key, typename info>
void Sequence<key, info>::swap(Sequence<key, info>& s)
{
	Node *tFirst = this->first;
	Node *tLast = this->last;
	int tLen = this->len;
	this->first = s.first;
	this->last = s.last;
	this->len = s.len;
	s.first = tFirst;
	s.last = tLast;
	s.len = tLen;
}
#endif