#include <iostream>
#include "sll.hpp"
#include "tests.cpp"
using namespace std;

int main()
{
    
    // Sequence<int, int> oneList;
    // oneElem(oneList);
    // Sequence<int, int> noList;
    // noElem(noList);
    // Sequence<int, int> fiveList;
    // fiveElemTests(fiveList);

    
    Sequence<int, int> source, result1, result2;
    for (int i = 1; i < 6; i++)
    {
        source.pushBack(i, i * 5);
    }
    source.split(result1, 2, 1, result2, 2, 1);
    cout << "Source: " << source << ", Length = " << source.length() << endl;
    cout << "Result1: " << result1 << ", Length = " << result1.length() << endl;
    cout << "Result2: " << result2 << ", Length = " << result2.length() << endl;
    testSwap(result1, result2);
    cout << "Using remove on last element" << endl;
    result2.remove(2);
    cout << "Result2: " << result2 << ", Length = " << result2.length() << endl;
    return 0;
}