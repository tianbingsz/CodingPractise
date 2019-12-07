/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

Solution:
Sliding window, assume s[i, j), j >= i is substr without duplication, then move j forward until
s[j] hit duplication. After that, move i forward for the next longest substr without dup.
*/
// O(N), sliding window
class Solution {
public:
    int lengthOfLongestSubstring(string str) {
        unordered_set<char> cs;
        int s = 0, e = 0;
        int mlen = 0;
        // find longest str[s, e) without duplication
        while(s < str.size() && e < str.size()) {
            if (cs.count(str[e]) == 0) {// expand window
                cs.insert(str[e]); ++e;
                mlen = max(mlen, e - s);
            } else { //dup str[e], stop at e, shrink window
                cs.erase(str[s]); ++s;
            }
        }
        return mlen;
    }
};
