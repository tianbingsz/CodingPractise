/*
Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character
Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

*/
// Time O(mn), beat 92%
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        if (n == 0) return m;
        if (m == 0) return n;
        vector<vector<int>> cost(n+1, vector<int>(m+1, 0));
        for (int i = 1; i <= n; ++i) {
            cost[i][0] = i; // delete
        }
        for (int j = 1; j <=m; ++j) {
            cost[0][j] = j; // insert
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int curCost = INT_MAX;
                if (word1[i-1] == word2[j-1]) {
                    // match i-th and j-th chars
                    curCost = cost[i-1][j-1]; 
                } else {
                    curCost = cost[i-1][j-1] + 1; // replace
                }
                // delete or insert
                cost[i][j] = std::min(curCost, 
                                      1 + std::min(cost[i-1][j], cost[i][j-1]));
            }
        }
        return cost[n][m];
    }
};
