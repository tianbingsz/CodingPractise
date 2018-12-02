/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1; if version1 < version2 return -1;otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Example 1:

Input: version1 = "0.1", version2 = "1.1"
Output: -1
Example 2:

Input: version1 = "1.0.1", version2 = "1"
Output: 1
Example 3:

Input: version1 = "7.5.2.4", version2 = "7.5.3"
Output: -1
Solution:
1. split version string into vector of numbers
2. compare vector of numbers one by one
*/
// O(N), 0 ms, 100%
class Solution {
public:
    int compareVersion(string version1, string version2) {
        auto v1 = split(version1);
        auto v2 = split(version2);
        int n = std::min(v1.size(), v2.size());
        for (int i = 0; i < n; ++i) {
            if (v1[i] > v2[i]) return 1;
            if (v1[i] < v2[i]) return -1;
        }
        // v1[1..n] == v2[1..n]
        if (v1.size() > n) {
            for (int i = n; i < v1.size(); ++i) {
                if (v1[i] != 0) return 1;
            }
            return 0; // v1[n .. end] = 000
        }
        if (v2.size() > n) {
            for (int i = n; i < v2.size(); ++i) {
                if (v2[i] != 0) return -1;
            }
            return 0; // v1[n .. end] = 000
        }
        // v1[1..n] == v2[1..n] and |v1| = |v2|
        return 0; // the same
    }
private:
    vector<int> split(const string &s) {
        vector<int> res;
        int start = 0;
        int end = string::npos;
        while ((end = s.find('.', start)) != string::npos) {
            res.push_back(stoi(s.substr(start, end - start)));
            if (end + 1 < s.size() && s[end+1] != '.') start = end + 1;
        }
        if (start < s.size()) res.push_back(stoi(s.substr(start)));
        return res;
    }
};
