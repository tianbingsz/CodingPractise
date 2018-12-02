/*
Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:

Input: "aba"
Output: False
Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)

Naive Solution: 
find each candidate substring from len = n/2 until 1, 
to see if we can repeate n/len times of substring to be equal to string?
*/
// O(N^2), 36 ms
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        if (s.empty()) return false;
        int n = s.size();
        for (int l = n/2; l >= 1; --l) {
            if(n % l == 0) {
                // check s is n/l copies of s[0..l-1]
                if (checkRepeat(s, l)) return true;
            }    
        }
        return false;
    }
private:
    bool checkRepeat(string &s, int len) {
        string repeat;
        for (int i = 0; i < s.size() / len; ++i) {
            repeat += s.substr(0, len);
        }
        return s == repeat;
    }
};

/*
Optimized Solution:
left | right, if left is one duplicate of the substring
then left | right == right | left
E.g. X | (X) == (X) | X or X | (XXXX) == (XXXX) | X 
*/
// O(N^2), 20 ms, beat 97.62%
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        if (s.empty()) return false;
        int n = s.size();
        for (int l = n/2; l >= 1; --l) {
            if(n % l == 0) {
                // s = left | right, rotate = right | left
                if (checkRotate(s, l)) return true;
            }    
        }
        return false;
    }
private:
    bool checkRotate(const string &s, int len) {
        string rotate = s.substr(len);
        rotate += s.substr(0, len);
        return s == rotate;
    }
    
};

