#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <bits/stdc++.h>
using namespace std;


vector<int> isSafe(vector<int> rowNumList) {
    vector<int> unsafeIndexes;
    int prevLevel = rowNumList.at(0);
    int level;
    bool isIncreasing;
    unsafeIndexes.push_back(-1);

    if (rowNumList.at(0) == rowNumList.at(1)) {
        unsafeIndexes.push_back(1);
        unsafeIndexes.push_back(0);
        // cout << "Unsafe bc not moving" << endl;
        isIncreasing = false;
    } else if (rowNumList.at(0) > rowNumList.at(1)) {
        isIncreasing = false;
    } else if (rowNumList.at(0) < rowNumList.at(1)) {
        isIncreasing = true;
    }

    // cout << "isIncreasing " << isIncreasing << endl;
    
    for (int i = 1; i < rowNumList.size(); i++)
    {

        level = rowNumList.at(i);
        
        if (isIncreasing) {
            if (level - prevLevel < 1 || level - prevLevel > 3) {
                unsafeIndexes.push_back(0);
                unsafeIndexes.push_back(i);
                unsafeIndexes.push_back(i-1);
            }
        }

        if (isIncreasing == false) {
            if (prevLevel - level < 1 || prevLevel - level > 3) {
                unsafeIndexes.push_back(0);
                unsafeIndexes.push_back(i);
                unsafeIndexes.push_back(i-1);
            }
        }

        prevLevel = level;
    }

    // -1 if safe
    return unsafeIndexes;

}


int main(int argc, char const *argv[])
{
    fstream MyFile("data");

    string delimiter = " ";

    string line;

    vector<int> rowNumList = vector<int>();
    vector<int> dist = vector<int>();

    int safesum = 0;

    map<int, int> coordFreq;

    while (MyFile.peek() != -1) {
        rowNumList.clear();

        getline(MyFile, line);

        while (line.find(delimiter) != -1) {
            rowNumList.push_back(stoi(line.substr(0, line.find(delimiter))));
            line.erase(0, line.find(delimiter) + delimiter.length());
        }
        rowNumList.push_back(stoi(line));

        // Actually check if it's safe:

        vector<int> unsafeIndexVec = isSafe(rowNumList);
        // there may be duplicate indexes in the vector above but that should not be a major problem.

        if (unsafeIndexVec.size() == 1) {
            safesum++;
        } else {
            // Problem Dampener

            bool problemDampenerSuccess = false;
            
            unsafeIndexVec.erase(unsafeIndexVec.begin());

            cout << "New line!" << endl;
            
            
            for (int index : unsafeIndexVec) {
                cout << "index: " << index << endl;

                vector<int> copyof_rowNumList(rowNumList);
                for (int i : copyof_rowNumList) {
                    cout << i << " ";
                }
                cout << endl;
                

                copyof_rowNumList.erase(copyof_rowNumList.begin() + index);
                for (int i : copyof_rowNumList) {
                    cout << i << " ";
                }
                cout << endl;

                // Retry the problem
                
                vector<int> retryUnsafeIndexVec = isSafe(copyof_rowNumList);

                for (int i : retryUnsafeIndexVec) {
                    cout << i << " ";
                }
                cout << endl;
                if (retryUnsafeIndexVec.size() == 1) {
                    cout << "Safe!" << endl;
                    problemDampenerSuccess = true;
                }

            }
            cout << "Safe? " << problemDampenerSuccess << endl;

            if (problemDampenerSuccess) {
                safesum++;
            }
        }
    }

    cout << safesum << endl;

    return 0;
}