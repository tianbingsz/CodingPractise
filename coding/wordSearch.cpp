/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example:

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.

Solution: DFS
Search(word, m)
for i in [1..n]:
    for j in [1..m]:
        if (m[i][j] == word[0]):
            visited[i][j] = true
            // able to find word
            if DFS(word, m, 1, i, j) == true: return true
            visited[i][j] = false
DFS(word, m, end, x, y):
    if end == word.size: return true; //find word
    for d in directions:
        nx = x + dx, ny = y + dy
        if valid(nx,ny) and !visited[nx][ny] and word[end] == m[nx][ny]:
            visited[nx][ny] = true
            if DFS(word, m, end + 1, nx, ny) == true: return true // find
            visited[nx][ny] = false 
    return false // not find
*/
// 24 ms
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty()) return false;
        if (word.empty()) return false;
        int n = board.size();
        int m = board[0].size();
        if (word.size() > n*m) return false;
        
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] != word[0]) continue;
                visited[i][j] = true;
                if (dfs(board, word, 1, i, j, visited)) return true;
                visited[i][j] = false;
            }
        }
        return false;
    }
    
private:
    vector<vector<int>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    bool dfs(const vector<vector<char>> &board, 
             const string &word, 
             int end, int x, int y,
             vector<vector<bool>> &visited) {
        if (end == word.size()) return true;
        int n = board.size();
        int m = board[0].size();
        for (const auto &d : dirs) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (nx < 0 || nx >=n || ny < 0 || ny >= m) continue;
            if (visited[nx][ny]) continue;
            if (word[end] != board[nx][ny]) continue;
            visited[nx][ny] = true;
            if (dfs(board, word, end+1, nx, ny, visited)) return true;
            visited[nx][ny] = false;
        }
        return false;
    }
};
