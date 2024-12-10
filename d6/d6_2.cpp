
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;


bool nextIsOutside(vector<int> guardPos, vector<vector<char>> rowList, int guardDir) {

    if (guardDir == 1) {
        guardPos.at(1) -= 1;
        
        if (guardPos.at(1) < 0 || guardPos.at(1) >= rowList.at(0).size() || guardPos.at(0) < 0 || guardPos.at(0) >= rowList.size()) {
            // Hit edge, this is the last one but we have more to search for than fits
            //cout << "edge detected:" << endl;
            //cout << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl;
            return true;
        }
        guardPos.at(1) += 1;
    }
    if (guardDir == 2) {
        guardPos.at(0) += 1;
        
        if (guardPos.at(1) < 0 || guardPos.at(1) >= rowList.at(0).size() || guardPos.at(0) < 0 || guardPos.at(0) >= rowList.size()) {
            // Hit edge, this is the last one but we have more to search for than fits
            //cout << "edge detected:" << endl;
            //cout << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl;
            return true;
        }
        guardPos.at(0) -= 1;
    }
    if (guardDir == 3) {
        guardPos.at(1) += 1;
        
        if (guardPos.at(1) < 0 || guardPos.at(1) >= rowList.at(0).size() || guardPos.at(0) < 0 || guardPos.at(0) >= rowList.size()) {
            // Hit edge, this is the last one but we have more to search for than fits
            //cout << "edge detected:" << endl;
            //cout << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl;
            return true;
        }
        guardPos.at(1) -= 1;
    }
    if (guardDir == 4) {
        guardPos.at(0) -= 1;
        
        if (guardPos.at(1) < 0 || guardPos.at(1) >= rowList.at(0).size() || guardPos.at(0) < 0 || guardPos.at(0) >= rowList.size()) {
            // Hit edge, this is the last one but we have more to search for than fits
            //cout << "edge detected:" << endl;
            //cout << "pos " << pos.at(0) << " " << pos.at(1) << " dir " << dir.at(0) << " " << dir.at(1) << endl;
            return true;
        }
        guardPos.at(0) += 1;
    }   
    return false;
}

bool isLoop(vector<int> guardPos, vector<vector<char>>& rowList, int guardDir) {
    map<vector<int>, int> positionMap;

    // Move guard around
    bool outside = false;
    bool foundLoop = false;
    bool nextWall;
    while (!outside && !foundLoop) {
        // Check if looped

        for(auto const [pos, num] : positionMap) {
            if (num > 4) {
                foundLoop = true;
            }
        }

        // check next step

        //cout << guardPos.at(0) << endl;
        //cout << guardPos.at(1) << endl;

        if (nextIsOutside(guardPos,rowList,guardDir)) {
            rowList.at(guardPos.at(1)).at(guardPos.at(0)) = 'X';
            outside = true;
            break;
        }

        nextWall = false;
        if (guardDir == 1) {
            if (rowList.at(guardPos.at(1)-1).at(guardPos.at(0)) == '#') {
                nextWall = true;
            }
        }
        if (guardDir == 2) {
            if (rowList.at(guardPos.at(1)).at(guardPos.at(0)+1) == '#') {
                nextWall = true;
            }
        }
        if (guardDir == 3) {
            if (rowList.at(guardPos.at(1)+1).at(guardPos.at(0)) == '#') {
                nextWall = true;
            }
        }
        if (guardDir == 4) {
            if (rowList.at(guardPos.at(1)).at(guardPos.at(0)-1) == '#') {
                nextWall = true;
            }
        }   

        if (!nextWall) {
            if (positionMap.find({guardPos.at(0), guardPos.at(1)}) != positionMap.end()) {
                positionMap.at({guardPos.at(0), guardPos.at(1)})++;
            } else {
                positionMap.insert({{guardPos.at(0), guardPos.at(1)}, 1});
            }
            
            rowList.at(guardPos.at(1)).at(guardPos.at(0)) = 'X';
            if (guardDir == 1) {
                guardPos.at(1) -= 1;
            }
            if (guardDir == 2) {
                guardPos.at(0) += 1;
            }
            if (guardDir == 3) {
                guardPos.at(1) += 1;
            }
            if (guardDir == 4) {
                guardPos.at(0) -= 1;
            }
        } else {
            if (guardDir == 4) {
                guardDir = 1;
            } else {
                guardDir++;
            }
        }

    }


    if (foundLoop) {
        return true;
    } else if (outside) {
        return false;
    } else {return false;}
}

int main(int argc, char const *argv[])
{

    ofstream outFile("output.txt");
    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    fstream MyFile("data");

    string line;

    int XMASSum = 0;

    vector<int> guardPos = {-1,-1};
    int guardDir = 1; // 1,2,3 or 4 for N W S E


    vector<vector<char>> rowList = vector<vector<char>>();

    // Read map 
    int i = 0;
    int j = 0;
    while (MyFile.peek() != -1) {
        vector<char> elementList = vector<char>();
        i = 0;

        getline(MyFile, line);

        for (char c : line) {
            elementList.push_back(c);
            if (c == '^') {
                guardPos.at(0) = i;
                guardPos.at(1) = j;
            }
            i++;
        }

        rowList.push_back(elementList);
        j++;

    }

    for (vector<char> r : rowList) {
        for (int e : r) {
            printf("%c",e);

        }
        cout << endl;
    }

    // run through map once. Then check for each possible X in the map if adding an obstacle there would help

    isLoop(guardPos,rowList,guardDir);

    // check for each X
    int noWorking = 0;
    int noNotWorking = 0;

    i = 0;
    j = 0;
    for (vector<char> r : rowList) {
        i = 0;
        for (char e : r) {
            if (e == 'X') {
                // this cell has been visited. Let's just check it
                vector<vector<char>> rowListCopy(rowList);

                rowListCopy.at(j).at(i) = '#';
                if (isLoop(guardPos,rowListCopy,guardDir)) {
                    XMASSum++;
                    noWorking++;
                    //cout << "\nAddition worked!" << endl;
                    //cout << "At: " << i << " " << j << " \n" << endl;
                } else {
                    //cout << "Checked addition, didn't work" << endl;
                    noNotWorking++;
                }

                cout << "Working: " << noWorking << "  Not working: " << noNotWorking << endl;
                outFile << "On line: " << noWorking + noNotWorking << "Working: " << noWorking << "  Not working: " << noNotWorking << endl;

            }
            i++;
        }
        j++;
    }
    


    cout << XMASSum << endl;

    outFile << XMASSum << endl;
    outFile.close();

    return 0;
}

