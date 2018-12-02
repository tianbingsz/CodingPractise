/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.

Solution: Two Pointers
http://www.cnblogs.com/grandyang/p/4340948.html
Maitain a sliding window S[left, right]
Expand: the occurance of chars of T in S[left, right] < T.size:
    ++right, if(--letterCnt[s[right]] >= 0) ++cnt
Shrink: we find the same (or more) number of chars of T in S[left, right]
    while (cnt == T.size):
        mlen = min(mlen, right - left + 1)
        if S[left] appears at T and if(++letterCnt[s[left]] > 0) --cnt
        move left forward
*/
// O(N), 4 ms, 100%, Sliding Window
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> letterCnt(128, 0);
        for (char c : t) {
            ++letterCnt[c]; // only record letter in T
        }
        int mlen = INT_MAX;
        string res;
        int left = 0;
        int cnt = 0; // how many letters in S also in T
        for (int right = 0; right < s.size(); ++right) {
            // for letter in S not T, decrease to negative
            // only letter both in S and T, will decrease to >=0
            if (--letterCnt[s[right]] >= 0) ++cnt;
            while (cnt == t.size()) {
                // find a window, further shrink [left, right]
                if (mlen > right - left + 1) {
                    mlen = right - left + 1;
                    res = s.substr(left, mlen);
                }
                // find a letter of S in T,
                // for letter in S not T, the increment will <= 0
                if (++letterCnt[s[left]] > 0) --cnt;
                ++ left; // move left forward,
            }
        }
        return res;
    }
};
