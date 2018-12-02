/*

In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Solution:
As for undirected graph, for edge (u, v), if there exists a different path from u ---> v,
then u, v is the duplicated edge. We can use DFS to find a path between u, v given the current graph,
while the graph is growing.
graph = {}
For each coming edge (u, v):
    if we can find a path from u to v in graph, that implies edge(u,v) is duplicated
    otherwise, add edge to graph, graph U (u,v)
*/
// Time O(N^2), Space O(N)
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        if (edges.empty() || edges[0].empty()) return {};
        vector<int> res;
        unordered_map<int, vector<int>> graph;
        for (const auto &edge : edges) {
            int u = edge[0], v = edge[1];
            unordered_set<int> visited;
            if (hasPath(graph, u, v, visited)) {
            // there exists a path u ->...->v and v->u connected
                return edge;
            }
            // build graph continously
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        return {}; //no redudent edge
    }
    
    // dfs to find a path between u, v
    bool hasPath(unordered_map<int, vector<int>> &graph, 
                 int u, int v, unordered_set<int> &visited) {
        if (u == v) return true;// path node u = v
        visited.insert(u);
        for (int w : graph[u]) {
            if (visited.count(w)) continue; // already visited
            if (hasPath(graph, w, v, visited)) return true;
        }
        return false;
    }
};
