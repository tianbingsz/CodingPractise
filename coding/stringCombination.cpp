/*
20 Find Case Combinations of a String
Find all the combinations of a string in lowercase and uppercase. For example, string "ab" >>> "ab", "Ab", "aB", "AB". So, you will have 2^n (n = number of chars in the string) output strings. The goal is for you to test each of these strings and see if it matchs a hidden string.

Solution: binary representation, bit manipulation
00000
00001
,,,,,
11111

if set 1, upper case, otherwise, lower case
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool bitSet(int n, int offset) {
    return ((n >> offset ) & 1) != 0;
}

vector<string> stringCombination(const string &s) {
    if (s.empty()) return {};
    int n = s.size();
    int npow = pow(2, n);
    vector<string> res;
    for (int i = 0; i < npow; ++i) {
        string str(n, '*');
        for (int j = 0; j < n; ++j) {
            str[j] = bitSet(i,j) ? toupper(s[j]) : tolower(s[j]);
        }
        cout << "i, " << i << " str: " << str << endl;
        res.push_back(str);
    }
}

int main()
{
    cout<<"Hello World";
    auto slist = stringCombination("air");
    for (string &str: slist) cout << str << endl;
    return 0;
}

