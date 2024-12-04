#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;


bool findString(vector<vector<char>> board, vector<char> toFind, vector<int> pos, vector<int> dir) { // board, Chars to find (vector), position (index 0 over columns (x-axis), index 1 over rows (y-axis)), direction
    //cout << "   Let's go! " << endl << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl << toFind.at(0) << endl;
    
    if (toFind.size() == 1) {
        // This is the last one. Still, we have to check if the next one works.
        //cout << "Last one" << endl;
        //printf("%c",toFind.at(0));
        //printf("%c",board.at(pos.at(1)).at(pos.at(0)));
        return board.at(pos.at(1)).at(pos.at(0)) == toFind.at(0);
    } else {
        // edge detection
        pos.at(0) += dir.at(0);
        pos.at(1) += dir.at(1);
        
        if (pos.at(0) < 0 || pos.at(0) >= board.at(0).size() || pos.at(1) < 0 || pos.at(1) >= board.size()) {
            // Hit edge, this is the last one but we have more to search for than fits
            //cout << "edge detected:" << endl;
            //cout << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl;
            return false;
        }
        pos.at(0) -= dir.at(0);
        pos.at(1) -= dir.at(1);
    }

    bool nextWorks = board.at(pos.at(1) + dir.at(1)).at(pos.at(0)+dir.at(0)) == toFind.at(1);

    //cout << "nextworks: " << nextWorks << endl << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl << toFind.at(0) << endl;


    if (nextWorks) {
        // Move one further
        pos.at(0) += dir.at(0);
        pos.at(1) += dir.at(1);
        toFind.erase(toFind.begin());
        bool found = findString(board, toFind, pos, dir);
        return found;
    } else {
        return false;
    }

}


int main(int argc, char const *argv[])
{
    fstream MyFile("data");

    string line;

    int XMASSum = 0;

    vector<vector<int>> dirList = {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}};
    vector<vector<int>> diagDirList = {{1,1}, {1,-1}, {-1,-1}, {-1,1}};
    vector<vector<int>> MASDirList = {{0,2}, {2,0}, {0,-2}, {-2,0}};

    vector<vector<char>> rowList = vector<vector<char>>();

    while (MyFile.peek() != -1) {
        vector<char> elementList = vector<char>();

        getline(MyFile, line);

        for (char c : line) {
            elementList.push_back(c);
        }

        rowList.push_back(elementList);
    }

    for (vector<char> r : rowList) {
        for (int e : r) {
            printf("%c",e);

        }
        cout << endl;
    }

    // Row search
    for (int i = 0; i < rowList.size(); i++)
    {
        for (int j = 0; j < rowList.at(0).size(); j++)
        {
            if (rowList.at(i).at(j) == 'M') {
                vector<char> toFind = {'M', 'A', 'S'};
                vector<int> pos = {j, i};
                vector<int> dir;

                // // Horizontal search
                // if (findString(rowList, toFind, pos, dirList.at(1))) {XMASSum++;}
                // if (findString(rowList, toFind, pos, dirList.at(5))) {XMASSum++;}

                // // Vertical
                // if (findString(rowList, toFind, pos, dirList.at(7))) {XMASSum++;}
                // if (findString(rowList, toFind, pos, dirList.at(3))) {XMASSum++;}

                // // Diagonal
                // if (findString(rowList, toFind, pos, dirList.at(0))) {XMASSum++;}
                // if (findString(rowList, toFind, pos, dirList.at(2))) {XMASSum++;}
                // if (findString(rowList, toFind, pos, dirList.at(4))) {XMASSum++;}
                // if (findString(rowList, toFind, pos, dirList.at(6))) {XMASSum++;}

                // Searching for X of MAS:
                // This code will suck

                // Check if there is a MAS in any direction
                bool isMAS = false;
                
                for (vector<int> d : diagDirList) {
                    dir = d;
                    if (findString(rowList, toFind, pos, dir)) {
                        
                        // Save the position of the A for later use
                        vector<int> APos = {pos.at(0)+dir.at(0), pos.at(1)+dir.at(1)};

                        // Now check each possible start for the next MAS two in either cardinal direction
                        vector<int> testPos = vector<int>(pos);
                        for (vector<int> d : MASDirList) {
                            dir = d;

                            // edge detection
                            testPos.at(0) += dir.at(0);
                            testPos.at(1) += dir.at(1);
                            
                            if (testPos.at(0) < 0 || testPos.at(0) >= rowList.at(0).size() || testPos.at(1) < 0 || testPos.at(1) >= rowList.size()) {
                                // Hit edge,
                            } else {
                                // No edge yet, check for MAS here

                                if (rowList.at(testPos.at(1)).at(testPos.at(0)) == 'M') {
                                    for (vector<int> d : diagDirList) {
                                        dir = d;
                                        if (findString(rowList, toFind, testPos, dir)) {
                                            // Check if the MAS goes through the same A as the last one
                                            if (testPos.at(0)+dir.at(0) == APos.at(0) && testPos.at(1)+dir.at(1) == APos.at(1)) {
                                                // check so that they are not the same (for some reason this happens)
                                                if (testPos.at(0) == pos.at(0) && testPos.at(1) == pos.at(1)) {
                                                    // WHat!
                                                    cout << "Found impostor" << endl;
                                                } else {
                                                    XMASSum++;

                                                    cout << "Found a MAS: " << XMASSum << endl;
                                                    // cout << "Prev A at:" << APos.at(0) << " " << APos.at(1) << endl;
                                                    // cout << "dir: " << dir.at(0) << " " << dir.at(1) << endl;
                                                    // cout << "old M pos:" << pos.at(0) << " " << pos.at(1) << endl;
                                                    // cout << "new M pos:" << testPos.at(0) << " " << testPos.at(1) << endl;

                                                    // Now we have to destroy the X. We remove the A in the middle.
                                                    rowList.at(APos.at(1)).at(APos.at(0)) = '.';
                                                }
                                            }                       
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }   
    }

    for (vector<char> r : rowList) {
        for (int e : r) {
            printf("%c",e);

        }
        cout << endl;
    }

    cout << XMASSum << endl;
    

    return 0;
}

