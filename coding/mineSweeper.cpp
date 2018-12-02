/*
Let's play the minesweeper game (Wikipedia, online game)!

You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:
Solution: DFS(x,y)
1.If a mine ('M') is revealed, then the game is over - change it to 'X'.
2. If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
3. If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
Example 1:
Input: 

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]


*/
// O(MN), DFS, beat 100%
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        if (board.empty() || board[0].empty()) return board;
        dfs(board, click[0], click[1]);
        return board;
    }

private:
    vector<int> dx{-1, 0, 1};
    vector<int> dy{-1, 0, 1};
    void dfs(vector<vector<char>> &board, int x, int y) {
        int n = board.size();
        int m = board[0].size();
        if (x < 0 || x >= n || y < 0 || y >= m) return;
        if (board[x][y] == 'M') {
            board[x][y] = 'X'; return;
        }
        if (board[x][y] != 'E') return;
        int nMines = 0;
        for (int d0 : dx) {
            for (int d1 : dy) {
                if (d0 == 0 && d1 == 0) continue;
                int nx = x + d0, ny = y + d1;
                if (nx >= 0 && nx < n && ny >=0 && ny < m && board[nx][ny] == 'M')
                    ++nMines;
            }
        }
        if (nMines > 0) {
            board[x][y] = nMines + '0';
            return;
        }
        board[x][y] = 'B';
        for (int d0 : dx) { // expand recursively
            for (int d1 : dy) {
                if (d0 == 0 && d1 == 0) continue;
                dfs(board, x + d0, y + d1);
            }
        }
    }
};
