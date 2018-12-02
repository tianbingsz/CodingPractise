/*
An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
Solution: DFS or BFS, Connected Compenent traversal
*/
// DFS, O(MN), beat 99.09%
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (image.empty() || image[0].empty()) return image;
        int n = image.size();
        int m = image[0].size();
        if (sr < 0 || sr >=n || sc < 0 || sc >=m) return image;
        visited.assign(n, vector<bool>(m, false));
        int oldColor = image[sr][sc];
        image[sr][sc] = newColor;
        visited[sr][sc] = true;
        dfs(image, sr, sc, oldColor, newColor);
        return image;
    }

private:
    vector<vector<int>> delta{{1,0}, {-1,0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited;

    void dfs(vector<vector<int>> &image, int x, int y,
             int oldColor, int newColor) {
        int n = image.size();
        int m = image[0].size();
        for (const auto &d : delta) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (nx < 0 || nx >=n || ny < 0 || ny >=m) continue;
            if (visited[nx][ny] || image[nx][ny] != oldColor) continue;
            visited[nx][ny] = true;
            image[nx][ny] = newColor;
            dfs(image, nx, ny, oldColor, newColor);
        }
    }
};

// BFS, O(MN), beat 99.09%
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (image.empty() || image[0].empty()) return image;
        int n = image.size();
        int m = image[0].size();
        if (sr < 0 || sr >=n || sc < 0 || sc >=m) return image;
        int oldColor = image[sr][sc];
        visited.assign(n, vector<bool>(m, false));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        while(! q.empty()) {
            auto pos = q.front(); q.pop();
            int x = pos.first;
            int y = pos.second;
            visited[x][y] = true;
            image[x][y] = newColor;
            for (const auto & d : delta) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 0 || nx >=n || ny < 0 || ny >=m) continue;

                if (visited[nx][ny] || image[nx][ny] != oldColor) continue;
                q.push({nx, ny});
            }
        }
        return image;
    }

private:
    vector<vector<int>> delta{{1,0}, {-1,0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited;

};
