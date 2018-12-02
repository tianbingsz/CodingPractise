/*
Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:

Input: "hello"
Output: "holle"
Example 2:

Input: "leetcode"
Output: "leotcede"

*/
// https://leetcode.com/problems/reverse-vowels-of-a-string/description/
// O(N) beat 98.67%
class Solution {
public:
    string reverseVowels(string s) {
        if (s.size() < 1) return s;
        int i = 0, j = s.size() - 1;
        while(i < j) {
            if (isVowels(s[i]) && isVowels(s[j])) {
                // swap s[i], s[j]
                std::swap(s[i], s[j]);
                ++i; --j; continue;
            }
            if (!isVowels(s[i]) && !isVowels(s[j])) {
                ++i; --j; continue;
            }
            if (isVowels(s[i])) {
                --j; // keep i vowel
            } else {
                ++i; // keep j vowel
            }
        }
        return s;
    }

private:
    bool isVowels(char c) {
        string vowels = "aeiou";
        return vowels.find(tolower(c)) != std::string::npos;
    }
};
