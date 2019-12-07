/*
On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

Examples:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14

Solution: BFS 
https://www.cnblogs.com/grandyang/p/8955735.html
*/

// 8 ms, 99.34%
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        string target = "123450";
        string start;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                start += std::to_string(board[i][j]);
        }
        unordered_set<string> visited{start};
        queue<string> q;
        q.push(start);
        int step = 0;
        while(! q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string cur = q.front(); q.pop();
                if (cur == target) return step;
                int zero_idx = cur.find("0");
                for (int d : dirs[zero_idx]) {
                    string next = cur;
                    std::swap(next[d], next[zero_idx]);
                    if (visited.count(next)) continue;
                    visited.insert(next);
                    q.push(next);
                }
            }
            ++step;
        }
        return -1;
    }

private:
    vector<vector<int>> dirs = {{1,3}, {0,2,4}, {1,5}, {0,4}, {1,3,5}, {2,4}};
};
