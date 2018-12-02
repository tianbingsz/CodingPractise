/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:

Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 7

Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
             the point (1,2) is an ideal empty land to build a house, as the total
             travel distance of 3+3+1=7 is minimal. So return 7.
Solution: BFS
1. Staring from each building(grid[x,y]==1),
   use BFS to expand to each cell (0) labelling with the distance to the building, and accumulate
2. For each cell grid[i,j] == 0, if all buildings(1) reachable to it, find the accumulative dist :
    mDist = min(mDist, dist(i,j))
*/
// O(NM), 40 ms
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        // accumulative dist to each building
        vector<vector<int>> dist(n, vector<int>(m, 0));
        // # building expanding here
        vector<vector<int>> bCnt(n, vector<int>(m, 0));
        int nBuildings = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    ++nBuildings;
                    BFSExpansion(grid, dist, bCnt, i, j);
                }
            }
        }
        int mDist = INT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (bCnt[i][j] == nBuildings && grid[i][j] == 0) {
                    mDist = std::min(mDist, dist[i][j]);
                }
            }
        }
        return mDist == INT_MAX ? -1 : mDist;
    }
private:
    vector<vector<int>> delta = {{-1,0},{1,0}, {0,-1}, {0,1}};
    /*expand from building(1) to all 0s unitl hitting block (2) or new building (1)*/
    void BFSExpansion(const vector<vector<int>> &grid,
                     vector<vector<int>> &dist,
                     vector<vector<int>> &cnt, int x, int y) {
        int n = grid.size();
        int m = grid[0].size();
        int level = 0;
        queue<pair<int, int>> q;
        q.push({x, y});
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        while(! q.empty()) {
            ++level;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int x0 = q.front().first;
                int y0 = q.front().second;
                q.pop();
                for (const auto & d : delta) {
                    int nx = x0 + d[0];
                    int ny = y0 + d[1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && grid[nx][ny] == 0) {
                        dist[nx][ny] += level;
                        ++cnt[nx][ny];
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }
};
