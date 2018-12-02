/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
Example:

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
Solution: Divide and Condquer
set init val to compare m[i][j], i = 0, j = m-1 (last elem in the first row)
Iteratively for max n + m rounds:
    if m[i][j] == target: find, return
    if target > m[i][j]:
        keep j, rule out the remaining elem in i-th row (m[i][k<=j]) < target
        ++i
    if target < m[i][j]:
        keep i, rule out the remaining j-th col, as (m[k>=i][j]) > target
        --j
*/
// https://leetcode.com/problems/search-a-2d-matrix-ii/description/
// https://leetcode.com/submissions/detail/172932390/
class Solution {
public:
    // O(m + n)
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())  return false;
        int m = matrix.size(); // # row
        int n = matrix[0].size(); // # col
        if (target < matrix[0][0] || target > matrix[m-1][n-1])
            return false;
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            if (matrix[i][j] == target) return true;
            if (matrix[i][j] > target) {
                --j; // rule out col j, goto smaller col
            } else {
                ++i; // rule out row i, goto bigger row
            }
        }
        return false;
    }

};
