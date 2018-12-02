/*
An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.

graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.



Example 1:

Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
Example 2:

Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]


Note:

1 <= graph.length <= 12
0 <= graph[i].length < graph.length

Solution: BFS
visited[curNode][visitedState] to denote a unqiue path and current node
while (! q.empty())
    state = q.front().second
    if state == 111111 (1 << n - 1), we find a path visited every node.
    for next : neigh(cur):
        state |= 1 << next
        if (!visited[next][state]):
            visited[next][state] = true
            q.push({next, state})
Need to calc steps for the expansion for all the nodes in the queue
*/
// beat 99.75%, Time, Space O(N * 2^N), BFS
class Solution {
public:
  int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    int sol = (1 << n) - 1;
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(1 << n, false));
    for (int i = 0; i < n; ++i) {
        visited[i][1 << i] = true;
        q.push({i, 1 << i});
    }
    int steps = 0;
    while (!q.empty()) {
      int s = q.size();
      while (s--) {
        auto p = q.front(); q.pop();
        int node = p.first;
        int state = p.second;
        if (state == sol) return steps;
        for (int next : graph[node]) {
            if (!visited[next][state | (1 << next)])  {
                visited[next][state | (1 << next)] = true;
                q.push({next, state | (1 << next)});
            }
        }
      }
      ++steps; // # expansions
    }
    return -1;
  }
};
