/*
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/

// 24 ms, 76.06%, O(N)
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty() || p.empty() || s.size() < p.size()) return {};
        vector<int> m1(128, 0);
        vector<int> m2(128, 0);
        vector<int> res;
        for (int i = 0; i < p.size(); ++i) {
            ++m1[p[i]]; ++ m2[s[i]];
        }
        if (m1 == m2) res.push_back(0);
        for (int i = p.size(); i < s.size(); ++i) {
            ++m2[s[i]]; --m2[s[i- p.size()]];
            if (m1 == m2) res.push_back(i - p.size() + 1);
        }
        return res;
    }
    
};

// 944 ms, 1.68%. TODO, improve it 
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty() || p.empty() || s.size() < p.size()) return {};
        vector<int> res;
        for (int i = 0; i < s.size() + 1 - p.size(); ++i) {
            if (isAnagram(s.substr(i, p.size()), p)) res.push_back(i);
        }
        return res;
    }
private:
    bool isAnagram(const string &s, const string &p) {
        if (s.size() != p.size()) return false;
        vector<int> cnt(128, 0);
        for (char c : s) {
            ++cnt[c - '0'];
        }
        for (char c : p) {
            if (--cnt[c - '0'] < 0) return false;    
        }
        return true;
    }
};
