/*
Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.
Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

*/
// Time O(N), beat 98.87%
class Solution {
public:
    string reverseStr(string s, int k) {
        bool flip = true;
        for (int i = 0; i < s.size(); i += k) {
            if (flip) {
            // reverse each 2k, s[0..k], s[2k..3k]...s[2rk ..end]
                if (i + k < s.size()) {
                    revStr(s, i, i + k -1);
                } else {
                    revStr(s, i, s.size() - 1);
                }
            }
            flip = !flip;
        }
        return s;
    }
private:
    // reverse string s[start, end]
    void revStr(string &s, int start, int end) {
        while(start < end) {
            std::swap(s[start++], s[end--]);
        }
    }
};
