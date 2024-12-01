#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    fstream MyFile("data");

    string delimiter = "   ";

    string line;

    vector<int> coord1List = vector<int>();
    vector<int> coord2List = vector<int>();
    vector<int> dist = vector<int>();

    map<int, int> coordFreq;

    while (MyFile.peek() != -1) {

        getline(MyFile, line);

        coord1List.push_back(stoi(line.substr(0, line.find(delimiter))));
        line.erase(0, line.find(delimiter) + delimiter.length());

        coord2List.push_back(stoi(line));

    }
    
    // sort(coord1List.begin(), coord1List.end());
    // sort(coord2List.begin(), coord2List.end());

    // for (int i = 0; i < coord1List.size(); i++)
    // {
    //     dist.push_back(abs(coord1List.at(i) - coord2List.at(i)));
    // }

    // int sumtotal = 0;
    // for (int distance : dist) {
    //     sumtotal += distance;
    // }
    
    // cout <<sumtotal << endl;

    for (int i = 0; i < coord2List.size(); i++)
    {
        if (coordFreq.count(coord2List.at(i)) == 1) {
            coordFreq[coord2List.at(i)] += 1;
        } else {
            coordFreq[coord2List.at(i)] = 1;
        }
    }


    int sumtwotal = 0;
    for (int i = 0; i < coord1List.size(); i++)
    {
        if (coordFreq.count(coord1List.at(i)) == 1) {
            sumtwotal += coord1List.at(i)*coordFreq.at(coord1List.at(i));
        } else {
            // multiply by zero
        }
    }

    cout << sumtwotal << endl;
    
    

    return 0;
}
