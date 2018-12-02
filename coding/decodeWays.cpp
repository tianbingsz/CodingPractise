/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Solution:
dp[i]: # decode ways for string s[i, end]
s_i s_{i+1}, i = n-2 to 0
if s[i] - 0 in [0, 9], dp[i] = dp[i+1]
if s[i, i + 1] in [10, 26], dp[i] = dp[i+1] + dp[i+2]
*/
// beat 100%, DP, O(N)
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[n] = 1;
        int num = s[n - 1] - '0';
        if (num > 0) dp[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i) {
            num = s[i] - '0';
            if (num > 0) dp[i] = dp[i + 1]; // s[i, i + 1 ... end]
            num = 10 * num + s[i+1] - '0';
            if (num >= 10 && num <= 26) {
                dp[i] += dp[i+2]; // s[i,i+1] and s[i+2:]
            }
        }
        return dp[0];
    }
};
