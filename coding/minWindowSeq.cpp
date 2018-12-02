/*
Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.

If there is no such window in S that covers all characters in T, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example 1:

Input:
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation:
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.
Solution: DP
dp[i][j] = k, k is the starting idx of S, s.t. T[0..j] is the subseq of W = S[k...i], j <= i
Init: for j > i, dp[i][j] = -1
for j = 0, dp[i][0] = i
Recursion:
1. S[i-1] == T[j-1]
dp[i][j] =  dp[i-1][j-1]
2. otherwise
dp[i][j] = dp[i-1][j]
Finally,
Find the min len for all i in  dp[i][m]
http://www.cnblogs.com/grandyang/p/8684817.html
*/
// O(MN), 88 ms
class Solution {
public:
    // dp[i][j]: starting position for S[0...i] and T[0..j]
    // s.t. T[0...j] is subseq of W = S[dp[i][j]... j]
    string minWindow(string S, string T) {
        int n = S.size();
        int m = T.size();
        vector<vector<int>> dp(n+1, vector<int>(m + 1, -1));
        for (int i = 0; i <= n; ++i) dp[i][0] = i;
        int mlen = INT_MAX;
        int start = -1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= min(i, m); ++j) {
                dp[i][j] = (S[i-1] == T[j-1]) ? dp[i-1][j-1] : dp[i-1][j];
            }
            if (dp[i][m] != -1) {
                int len = i -  dp[i][m];
                if (mlen > len) {
                    mlen = len; start = dp[i][m];
                }
            }
        }
        return mlen == INT_MAX ? "" : S.substr(start, mlen);
    }
};
