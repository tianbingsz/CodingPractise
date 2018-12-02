/*
Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Solution:
Find K multiplication of string A, s.t. K*|A| > |B|
if B is the substring, B should be the substring of K mul of A or (K+1) mul of A
*/
// https://leetcode.com/problems/repeated-string-match/description/
// not fast enough, TODO, KMP
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        if (A.empty()) return -1;
        if (B.empty()) return 0;
        string multA = A;
        int dup = 1;
        while(multA.size() < B.size()) {
            ++dup; multA += A;
        }
        if (multA.find(B) != std::string::npos)
            return dup;
        multA += A;
        if (multA.find(B) == std::string::npos)
            return -1;
        return ++dup;
    }
};
