/*
Write a function that takes a string as input and returns the string reversed.

Example 1:

Input: "hello"
Output: "olleh"
Example 2:

Input: "A man, a plan, a canal: Panama"
Output: "amanaP :lanac a ,nalp a ,nam A"

*/
// O(N), 8 ms
class Solution {
public:
    string reverseString(string s) {
        int l = 0, r = s.size() - 1;
        while(l < r) {
            std::swap(s[l++], s[r--]);
        }
        return s;
    }
};
