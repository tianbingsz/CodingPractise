/*
You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to compute all possible states of the string after one valid move.

Example:

Input: s = "++++"
Output:
[
  "--++",
  "+--+",
  "++--"
]

*/
// O(N), 100%
class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> res;
        if (s.empty()) return res;
        for (int i = 0; i < s.size() - 1; ++i) {
            if (s[i] == '+' && s[i+1] == '+') {
                string t = s;
                t[i] = '-'; t[i+1] = '-';
                res.push_back(t);
            }
        }
        return res;
    }
};
