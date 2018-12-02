/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".
Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false

Soluton: DP
dp[i][j] = true: s[1...i] match p[1...j]
init dp[0][0] = true; {} match {}
row 0, {} match c*, * at j-th position, c at j-1, 0 match at j-2 position
dp[0][j + 1]  = dp [0][j-1] && p[j-1] == *
Recursion
case 1: i-th in s match j-th in p or p is '.'
dp[i][j] = dp[i-1][j-1] if p[j-1] == s[i-1] or p[j-1] == '.'
case  2: c(j-1)*(j)
dp[i][j] = dp[i][j-1] match until c (1 match)
    or dp[i][j-2] match before c (0 match)
case 2.b, 2+ match c:  i-th in s match j-1-th (c) in p or p is '.'
dp[i][j] = dp[i][j] || dp[i-1][j] if p[j-2] == '.' or p[j-2] == s[i-1]
*/

// DP, O(MN), beat 100%
class Solution {
public:
    // dp[i][j] = true: s[1...i] match p[1...j]
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m+1, false));
        dp[0][0] = true; // {} matched {}
        for (int j = 1; j <= m; ++j) {
            // {} match c*
            if (p[j] == '*') dp[0][j + 1] = dp[0][j-1];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j-1] == '.' || (p[j-1] == s[i-1])) {
                    // match j-th in p and i-th ins
                    dp[i][j] = dp[i-1][j-1]; continue;
                }
                if (j > 1 && p[j - 1] == '*') {
                    // j-th is *, c*, match 1 or 0 c
                    dp[i][j] = dp[i][j-1] || dp[i][j-2];
                    // match 2+ c of c*
                    if(p[j-2] == '.' || p[j-2] == s[i-1] /*match c*/) {
                        dp[i][j] = dp[i][j] || dp[i-1][j];
                    }
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
        if (*s == '\0' && *p == '\0') return true;
        if (*s == '\0' || *p == '\0') return false;
        if (*(p+1) == '*') return matchStar(s, *p, p + 2);
        if (*p == *s || *p == '.') return helper(++s, ++p);
        return false;
    }

    bool matchStar(const char *s, char match, const char *p) {
        do {
            if (helper(s, p)) return true;
        } while(s != '\0' && (*s++ == match || *p == '.'));
    }
};
