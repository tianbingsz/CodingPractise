/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false
Solution: DP
dp[i][j] = true if s[1..i] match t[1..j], 1-based index
init dp[0][0] = true {} matched {}
row 0, {} match *
dp[0][j] = dp[0][j-1] && p[j-1] == '*'
Recursion:
if p[j-1] == ? or p[j-1] == s[i-1] :
    dp[i][j] = dp[i-1][j-1] // match i-th in s and j-th in t
if p[j-1] == *:
    dp[i][j] = dp[i-1][j] (1+ matched with s[i, i+1...])
        || dp[i][j-1] (0 matched)
*/
// DP, O(MN), 63.46%
class Solution {
public:
    // dp[i][j] = true, s[1...i] match p[1...j]
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true; // {} match {}
        for (int j = 1; j <= m; ++j) {
            // {} match p, only if p = * matched
            if (p[j-1] == '*' && dp[0][j-1]) dp[0][j] = true;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j-1] == '?' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1]; // p[j] matched s[i]
                } else if (p[j-1] == '*') {
                    // p[j] '*':  0 matched dp[i-1][j], 1+ match dp[i][j-1]
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                }
            }
        }
        return dp[n][m];
    }
};


// backtracking, TLE
class Solution {
public:
    bool isMatch(string s, string p) {
        return helper(s.c_str(), p.c_str());
    }

private:
    bool helper(const char *s, const char *p) {
        if (*p == '\0') return *s == '\0';
        if (*s == '\0' || *p == '\0') return false;
        if (*p == '?' || *p == *s) return helper(++s, ++p);
        if (*p == '*') return matchStar(s, p+1);
        return false;
    }

    bool matchStar(const char *s, const char *p) {
        do {
            if(helper(s, p)) return true;
        } while(s != '\0' && ++s);
        return false;
    }
};
