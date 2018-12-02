/*
A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0), followed by some number of '1's (also possibly 0.)

We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.

Return the minimum number of flips to make S monotone increasing.

 

Example 1:

Input: "00110"
Output: 1
Explanation: We flip the last digit to get 00111.
Example 2:

Input: "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.
Example 3:

Input: "00011000"
Output: 2
Explanation: We flip to get 00000000.

Solution: DP
https://blog.csdn.net/fuxuemingzhu/article/details/83247054
dp[i][0] : min num of flips to make S[1..i] increasing and end with 0
dp[i][1]:  min num of flips S[1..i] ending with 1
init: dp[0][0] = 0, dp[0][1] = 0
for i = 1 to n:
    if S[i-1] == 0:
        // xxx0 0, xxx1 0
        dp[i][0] = dp[i-1][0] // not flip i-th char
        dp[i][1] = min(dp[i-1][0] + 1, dp[i-1][1] + 1) // flip i-th char to 1
    if S[i-1] == 1:
        // xxx0 1, xxx1 1
        dp[i][0] = dp[i-1][0] + 1 // flip i-th char to 0
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]) // not flip
return min(dp[n][0], dp[n][1])
*/
// 12 ms, 28.38%, O(N), DP
class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        for (int i = 1; i <= n; ++i) {
            if (S[i-1] == '0') {
                // XXX0 0, XXX1 0
                dp[i][0] = dp[i-1][0]; // not flip
                dp[i][1] = min(dp[i-1][0] + 1, dp[i-1][1] + 1); // flip
            }        
            if (S[i-1] == '1') {
                // xxx0 1 xxx1 1
                dp[i][0] = dp[i-1][0] + 1; // flip
                dp[i][1] = min(dp[i-1][0], dp[i-1][1]); // not flip
            }
        }
        return std::min(dp[n][0], dp[n][1]);
    }
};
