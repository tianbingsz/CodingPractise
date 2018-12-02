/*
Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".

Solution: DP
dp[i][j] : min operations for w1[1..i] and w2[1..j]
if w1[i] == w2[j]: dp[i][j] = dp[i-1][j-1], no operation needed
else: either delete w1[i] or w2[j]
      dp[i][j] = 1 + std::min(dp[i-1][j], dp[i][j-1]);
*/
// O(MN), 65.04%
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        // dp[i][j] : min operations for w1[1..i] and w2[1..j]
        vector<vector<int>> dp(n + 1, vector<int>(m+1));
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = i; // word1 compare with {}
        }
        for (int j = 1; j <= m; ++j) {
            dp[0][j] = j; // {} compare with word2
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    // delete either w1[i] or w2[j]
                    dp[i][j] = 1 + std::min(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][m];
    }
};
