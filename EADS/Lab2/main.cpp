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

    return 0;
}