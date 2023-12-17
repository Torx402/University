#include<iostream>
#include "ring.hpp"

using namespace std;

int main()
{
    Ring<int, int> list;
    list.push(1, 1);
    list.push(1, 2);
    list.push(1, 3);
    Ring<int, int>::Iter ptr(list);
    cout << *ptr << endl; 
    ++ptr;
    cout << *ptr << endl; 
    ++ptr;
    cout << *ptr << endl;

    return 0;
}