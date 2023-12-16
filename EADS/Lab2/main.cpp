#include<iostream>
#include "ring.hpp"

using namespace std;

int main()
{
    Ring<int, int> list;

    Ring<int, int>::Iter ptr;
    cout << *ptr << endl; 

    return 0;
}