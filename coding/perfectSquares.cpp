/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

Solution: DP
dp[0] = 0
dp[n] = min(dp[n - i * i] + 1, for 1 <= i <= sqrt(n))
*/
// O(N sqrt(N))
class Solution {
public:
    int numSquares(int n) {
        if (n <= 0) return 0;
        // dp[n] = min(dp[n - i * i] + 1, for 1 <= i <= sqrt(n))
        vector<int> dp({0}); // dp[0] = 0
        for (int m = 1; m <=n; ++m) {
            // dp[m] = min(dp[m - i * i] + 1, for 1 <= i <= sqrt(m))
            int minCnt = INT_MAX;
            for (int i = 1; i * i <= m; ++i) {
                minCnt = std::min(minCnt, dp[m - i * i] + 1);
            }
            dp.push_back(minCnt);
        }
        return dp[n];
    }  
};
