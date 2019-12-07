/*
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:

Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]] 
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
Example 2:

Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]] 
Explanation: The palindromes are ["battab","tabbat"]

Solution:
https://www.cnblogs.com/grandyang/p/5272039.html
Build a wordMap<words[i], i> to check if a word is in the map
Three cases:
1. bat <=> tab
for a string s in words: if reverse(s) also in words, we just find a pair
2. s = abc xx <=> cba
t = reverse(s) = xx cba
for a substr of reverse(s) in words: 
	say right = cba, rem = xx
	if rem is pal and right is in map: just find a pair
3. s = xx cba <=> abc
t = abc xx
for a substr of reverse(s) in words:
	say left = abc, rem = xx
	if rem is pal and left is in map: just find a pair
*/

// 256 ms, 48.76%
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        unordered_map<string, int> m;
        set<int> s;
        for (int i = 0; i < words.size(); ++i) {
            m[words[i]] = i;
            s.insert(words[i].size());
        }
        for (int i = 0; i < words.size(); ++i) {
            string t = words[i];
            reverse(t.begin(), t.end());
            if (m.count(t) && m[t] != i) {
                res.push_back({i, m[t]}); // bat <=> tab
            }
            int len = t.size();
            auto a = s.find(len);
            // for all valid substr with len < t.size()
            for (auto it = s.begin(); it != a; ++it) {
                int d = *it; // find string w len d (left or right)
                // [xx][cba], right cba with len 3
                if (isPal(t, 0, len - d - 1) && m.count(t.substr(len - d))) {
                    res.push_back({i, m[t.substr(len - d)]});
                }
                //[cba][xx], left cba with len 3
                if (isPal(t, d, len - 1) && m.count(t.substr(0, d))) {
                    res.push_back({m[t.substr(0, d)], i});
                }
            }
        }
        return res;
    }
    bool isPal(string t, int left, int right) {
        while (left < right) {
            if (t[left++] != t[right--]) return false;
        }
        return true;
    }
};
