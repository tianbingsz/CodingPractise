/*
Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False

*/
// O(N), beat 100%
class Solution {
public:
    bool detectCapitalUse(string word) {
        if (word.empty()) return false;
        if (word.size() == 1) return true;
        if (checkAllCap(word)) return true; // USA
        if (checkAllLower(word)) return true; // leetcode
        if (islower(word[0])) return false; // uSA
        return checkAllLower(word.substr(1)); // Google
    }

private:
    bool checkAllCap(const string &s) {
        for (char c : s) {
            if (islower(c)) return false;
        }
        return true;
    }

    bool checkAllLower(const string &s) {
        for (char c : s) {
            if (isupper(c)) return false;
        }
        return true;
    }

};

class Solution {
public:
    bool detectCapitalUse(string word) {
        int cnt = std::count_if(word.begin(), word.end(), 
                    [](char c){return c <= 'Z';}); 
        return cnt == 0 || cnt == word.size() || (cnt == 1 && word[0] <= 'Z'); 
    }
};

