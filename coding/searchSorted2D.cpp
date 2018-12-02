/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
Example 1:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
Output: true
Example 2:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
Output: false
Solution: Binary Search: log(M) + log(N)
1. find the row s.t. m[row][0] <= target < m[row+1][0]
2. find the col, s.t. m[row][col] == target, otherwise false
*/
// https://leetcode.com/submissions/detail/172559210/
// https://leetcode.com/problems/search-a-2d-matrix/description/
class Solution {
public:
    // log(m) + log(n)
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int nRow = matrix.size();
        int nCol = matrix[0].size();
        if (target < matrix[0][0] || target > matrix[nRow - 1][nCol -1])
            return false;
        
        // find the row where target would be
        int rs = 0, re = nRow - 1;
        while(rs <= re) {
            int m = rs + (re - rs)/2;
            if (matrix[m][0] == target) return true;
            if (matrix[m][0] < target) {
                rs = m + 1;
            } else { re = m - 1; }
        }
        int row = re; // m[re][0] <= target < m[rs][0]
        // find the column where target would be
        int cs = 0, ce = nCol - 1;
        while (cs <= ce) {
            int m = cs + (ce - cs)/2;
            if (matrix[row][m] == target) return true;
            if (matrix[row][m] < target) {
                cs = m + 1;
            } else { ce = m - 1; }
        }
        return false;
    }
};
