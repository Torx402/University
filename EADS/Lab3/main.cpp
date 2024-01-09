#include <iostream>
#include "Lab3.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include<bits/stdc++.h>



using namespace std;

int main(int argc, char *argv[]) 
{
    Dictionary<string, int> dict;
    string fileName = argv[1];
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "File not found" << endl;
        return 1;
    }

    string word;
    while (inFile >> word)
    {
        dict.insert(word, 1);
    }
    cout << dict << endl;
    inFile.close();
    return 0;
}