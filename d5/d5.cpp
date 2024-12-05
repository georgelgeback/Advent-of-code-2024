#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

bool listIsSorted(vector<vector<int>> rules, vector<int> lineList) {
    for (vector<int> rule : rules) {
        int savedNum = -1;
        for (int i = 0; i < lineList.size(); i++)
        {
            if (savedNum == -1) {
                if (lineList.at(i) == rule.at(1)) {
                    // Save the last number to check if the list follows the rule
                    savedNum = lineList.at(i);
                }
            } else {
                if (lineList.at(i) == rule.at(0)) {
                    // the order is wrong!
                    return false;
                }
            }
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{
    fstream MyFile("data");

    string delimiter = "|";
    string delimiter2 = ",";

    string line;

    vector<vector<int>> rules;

    int finalSum = 0;

    int rule1;
    int rule2;

    bool ruleRead = true;

    while (MyFile.peek() != -1) {

        getline(MyFile, line);
        if (line == "#") {ruleRead = false;}

        if (ruleRead) {
            rule1 = stoi(line.substr(0, line.find(delimiter)));
            line.erase(0, line.find(delimiter) + delimiter.length());
            rule2 = stoi(line);

            vector<int> ruleset = {rule1, rule2};

            rules.push_back(ruleset);
        } else if (line != "#") {
            vector<int> lineList;

            bool lineLegal = true;

            // Read all the data in the line
            while (line.find(delimiter2) != -1) {
                lineList.push_back(stoi(line.substr(0, line.find(delimiter2))));
                line.erase(0, line.find(delimiter2) + delimiter2.length());
            }
            lineList.push_back(stoi(line));


            // Check if line is according to rules
            lineLegal = listIsSorted(rules, lineList);

            if (!lineLegal) {
                bool unsorted = true;
                // Sort the list *sigh*
                int j = 0;
                while (unsorted) {
                    if (j > 10000) {
                        unsorted = false;
                        cout << "Failed to sort list: " << endl;
                    }

                    // Scramble rule elements
                    // Go through list and find rules that exist, switch them around and then recheck.
                    // Brute force, baby B)
                    vector<int> rule = rules.at(j % rules.size());

                    int index1 = -1;
                    int index2 = -1;
                    int savedNum = -1;
                     
                    for (int i = 0; i < lineList.size(); i++) {
                        if (index2 == -1) {
                            if (savedNum == -1) {
                                if (lineList.at(i) == rule.at(1)) {
                                    // Save the last number to check if the list follows the rule
                                    savedNum = lineList.at(i);
                                    index1 = i;
                                }
                            } else {
                                if (lineList.at(i) == rule.at(0)) {
                                    // the order is wrong!
                                    index2 = i;
                                }
                            }
                        }
                    }

                    if (index2 != -1) {
                        int temp = lineList.at(index1);

                        lineList.at(index1) = lineList.at(index2);
                        lineList.at(index2) = temp;
                        unsorted = !listIsSorted(rules, lineList);
                    }
                    j++;
                    
                }


                // Find the middle value and add it
                finalSum += lineList.at(lineList.size()/2);
                cout << "Sorted list" << endl;
            }
        }
    }

    cout << finalSum << endl;
    return 0;
}
