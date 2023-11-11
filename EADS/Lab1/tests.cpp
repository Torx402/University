#include <iostream>
#include "sll.hpp"
using namespace std;
/*
Methods to test:
insertAfter
pushFront
pushBack
remove
popFront
popBack
info front
bool front
bool back
bool getInfo
length
isempty
clear
search
operator<<
sort
reverse
swap
*/
//TODO
//add support for remove and insert for any list size (especially 1)

template <typename key, typename info>
void noElem(Sequence<key, info>& s)
{
    cout << "*** BEGIN TESTS FOR LIST WITH NO ELEMENT ***" << endl << endl;
    cout << "Testing insertAfter..." << endl;
    s.insertAfter(1, 2, 3);
    cout << "Testing remove..." << endl;
    s.remove(4);
    cout << "Testing popFront..." << endl;
    s.popFront();
    cout << "Testing popBack..." << endl;
    s.popBack();
    int x = -1;
    cout << "Testing front..." << endl;
    s.front(x);
    cout << "Front: " << x << endl;
    s.back(x);
    cout << "Testing back..." << endl;
    cout << "Back: " << x << endl;
    cout << "Testing getInfo..." << endl;
    s.getinfo(x, 1);
    cout << "getInfo: " << x << endl;
    cout << "Testing length..." << endl;
    cout << "Length = " << s.length() << endl;
    cout << "Testing isempty..." << endl;
    cout << "isempty = " << s.isempty() << endl;
    cout << "Testing clear..." << endl;
    s.clear();
    cout << "Testing search..." << endl;
    cout << "search = " << s.search(4) << endl;
    cout << "Testing reverse..." << endl;
    s.reverse();
    cout << "*** END TESTS FOR LIST WITH NO ELEMENT ***" << endl << endl;
}



template <typename key, typename info>
void oneElem(Sequence<key, info>& s)
{
    cout << "*** BEGIN TESTS FOR LIST WITH 1 ELEMENT ***" << endl << endl;
    //populate list with one element
    int k = 5;
    int i = 4;
    cout << "testing pushFront(5, 4) on empty list..." << endl;
    s.pushFront(k, i);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Clearing list..." << endl;
    s.clear();
    cout << "List: " << s << " Length = " << s.length() << endl << endl;
    cout << "testing pushBack(5, 4) on empty list..." << endl;
    s.pushBack(k, i);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing front..." << endl;
    int x = 0;
    s.front(x);
    cout << "Front Info: " << x << endl;
    cout << "Testing Back..." << endl;
    s.back(x);
    cout << "Back Info: " << x << endl << endl;

    cout << "Testing popFront..." << endl;
    s.popFront();
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "pushFront(5, 4)..." << endl;
    s.pushFront(k, i);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing popBack..." << endl;
    s.popBack();
    cout << "List: " << s << ", Length = " << s.length() << endl;
    cout << "pushFront(5, 4)..." << endl << endl;
    s.pushFront(k, i);

    cout << "Testing remove with key that does not exist..." << endl;
    cout << "remove(7)" << endl;
    s.remove(7);
    cout << "List: " << s << ", Length = " << s.length() << endl;
    cout << "Testing remove with key that exists..." << endl;
    cout << "remove(5)" << endl;
    s.remove(k);
    cout << "List: " << s << ", Length = " << s.length() << endl;
    cout << "pushFront(5, 4)..." << endl << endl;
    s.pushFront(k, i);

    cout << "Testing getInfo with key that exists..." << endl;
    cout << "getinfo(x, 4)" << endl;
    s.getinfo(x, k);
    cout << "getinfo: " << x << endl;
    cout << "Testing getInfo with key that does not exist..." << endl;
    cout << "getinfo(x, 7)" << endl;
    s.getinfo(x, 7);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing search with key that exists..." << endl;
    cout << "search(5)" << s.search(k) << endl;
    cout << "Testing search with key that does not exist..." << endl;
    cout << "search(7)" << s.search(7) << endl << endl;

    cout << "Testing reverse..." << endl;
    cout << "List: " << s << ", Length = " << s.length() << endl;
    cout << "*** END TESTS FOR LIST WITH 1 ELEMENT ***" << endl << endl;
}

template <typename key, typename info>
void fiveElemTests(Sequence<key, info>& s)
{
    cout << "*** BEGIN TESTS FOR LIST WITH 5 ELEMENTS ***" << endl << endl;
    
    // Add five elements to the list
    for (int i = 1; i <= 5; i++) {
        cout << "Inserting (key: " << i << ", info: " << i * 10 << ") at the end..." << endl;
        s.pushBack(i, i * 10);
    }

    cout << "List: " << s << ", Length = " << s.length() << endl << endl;
    
    cout << "Testing front..." << endl;
    int x = 0;
    s.front(x);
    cout << "Front Info: " << x << endl;
    
    cout << "Testing Back..." << endl;
    s.back(x);
    cout << "Back Info: " << x << endl << endl;

    cout << "Testing remove with key that does not exist..." << endl;
    cout << "remove(7)" << endl;
    s.remove(7);
    cout << "List: " << s << ", Length = " << s.length() << endl;

    cout << "Testing remove with key that exists..." << endl;
    cout << "remove(3)" << endl;
    s.remove(3);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing getInfo with key that exists..." << endl;
    s.getinfo(x, 2);
    cout << "getinfo(x, 2): " << x << endl;

    cout << "Testing getInfo with key that does not exist..." << endl;
    cout << "getinfo(x, 7)" << endl;
    s.getinfo(x, 7);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing search with key that exists..." << endl;
    cout << "search(4) = " << s.search(4) << endl;

    cout << "Testing search with key that does not exist..." << endl;
    cout << "search(7) = " << s.search(7) << endl << endl;

    cout << "Testing reverse..." << endl;
    cout << "Original: " << s << ", Length = " << s.length() << endl;
    s.reverse();
    cout << "Reversed: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing insertAfter..." << endl;
    cout << "insertAfter(2, 60, 2)" << endl;
    s.insertAfter(2, 60, 2);
    cout << "List: " << s << ", Length = " << s.length() << endl;
    cout << "Testing insertAfter after 2nd occurrance of key..." << endl;
    cout << "insertAfter(2, 80, 2, 2)" << endl;
    s.insertAfter(2, 80, 2, 2);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing popFront..." << endl;
    s.popFront();
    cout << "List: " << s << ", Length = " << s.length() << endl;

    cout << "Testing popBack..." << endl;
    s.popBack();
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing pushFront..." << endl;
    cout << "pushFront(0,0)" << endl;
    s.pushFront(0, 0);
    cout << "List: " << s << ", Length = " << s.length() << endl;

    cout << "Testing pushBack..." << endl;
    cout << "pushBack(6, 66)" << endl;
    s.pushBack(6, 66);
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing isempty..." << endl;
    cout << "isempty = " << s.isempty() << endl << endl;

    cout << "Testing search on existing key with different occurrances..." << endl;
    cout << "search(2, 1)" << s.search(2, 1) << endl;
    cout << "search(2, 2)" << s.search(2, 2) << endl;
    cout << "search(2, 3)" << s.search(2, 3) << endl;
    cout << "search(2, 4)" << s.search(2, 4) << endl << endl;

    cout << "Testing clear..." << endl;
    s.clear();
    cout << "List: " << s << ", Length = " << s.length() << endl << endl;

    cout << "Testing search on an empty list..." << endl;
    cout << "search(2) = " << s.search(2) << endl;

    cout << "*** END TESTS FOR LIST WITH 5 ELEMENTS ***" << endl << endl;
}

template <typename key, typename info>
void testSwap(Sequence<key, info>& first, Sequence<key, info>& second)
{
    cout << "*** BEGIN TESTS FOR SWAP ***" << endl << endl;
    cout << "Before swapping..." << endl;
    cout << "List1: " << first << ", Length = " << first.length() << endl;
    cout << "List2: " << second << ", Length = " << second.length() << endl;
    cout << endl << "After swapping..." << endl;
    first.swap(second);
    cout << "List1: " << first << ", Length = " << first.length() << endl;
    cout << "List2: " << second << ", Length = " << second.length() << endl;
}