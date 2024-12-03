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

    int sumof = 0;

    regex r("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
    smatch m;

    bool doMult = true;

    while (MyFile.peek() != -1) {

        getline(MyFile, line);

        while (regex_search(line, m, r)) {
            int num1 = 0;
            int num2 = 0;

            string str1;
            string str2; 
            string mulstr = m[0];

            line.erase(0, line.find(m[0]) + m[0].length());

            // use the mul

            // check if the mul is actually a do or don't

            if (mulstr.at(0) == 'd') {
                if (mulstr.length() == 4) {
                    // do()
                    doMult = true;
                } else {
                    doMult = false;
                }
            } else if (doMult) {
                str1 = mulstr.substr(0, mulstr.find(","));
                str2 = mulstr.substr(mulstr.find(",") + 1, mulstr.back());

                num1 = stoi(str1.substr(4, str1.back()));
                num2 = stoi(str2.substr(0, str1.back() -1));

                // cout << "Found: " << mulstr << endl;

                // cout << str1 << endl;
                // cout << str2 << endl;

                // cout << num1 << endl;
                // cout << num2 << endl;

                // Multiply numbers and add to sum

                sumof += num1*num2;
            }

        }

        
        

    }

    cout << sumof << endl;
    return 0;
}
