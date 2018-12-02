/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

*/
// beat 100%
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string out;
        helper(n, 0, 0, out);
        return res;
    }

private:
    vector<string> res;
    void helper(int n, int left, int right, string out) {
        if (left < right || left > n || right > n) return;
        // left >= right
        if (left == n && right == n) {
            res.push_back(out); return;
        }
        if (left == n && right < n) {
            helper(n, left, right + 1, out + ')'); return;
        }
        // left < n || right < n
        helper(n, left + 1, right, out + '(');
        helper(n, left, right + 1, out +')' );
    }
};
