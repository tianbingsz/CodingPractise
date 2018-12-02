/*
For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3

Output: [1]
Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5

Output: [3, 4]
Note:

According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.


Solution:
此题本质上求最长路径上的中间1-2个节点。由于根节点不确定，从叶节点出发，层层剥离，这就是拓扑排序(inDegree数组)。而且需要知道最后一层的1-2个节点，所以考虑用按层遍历BFS（两数组）。见KB。

注意事项：
由于最后一层可能是1-2个节点，所以要用一个变量把最后一层记录下来。
还有一点要注意的是这是无向图，所以入度=1而不是0时候即入队列。
Topological:

根据边统计每个节点的入度数记入in[i]
找出度数为0的节点加入到Queue
取出队首节点，把此节点邻接的节点度数减1，如果度数为0，加入到队列，循环直到队列为空
*/
// Time O(N), Space O(W), W is the width of graph, beat 95.99%
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        std::vector<std::vector<int>> adjacency_list(n);
        std::vector<int> degrees(n,0);
        for (const auto& p: edges) {
            adjacency_list[p.first].emplace_back(p.second);
            adjacency_list[p.second].emplace_back(p.first);
            ++degrees[p.first];
            ++degrees[p.second];
        }
        std::vector<bool> visited(n, false);
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (degrees[i] <= 1) { // find all leaves
                queue.push(i);
                visited[i] = true;
            }
        }
        while (!queue.empty() && n > 2) {
            int len = queue.size();
            for (int i = 0; i < len; ++i) {
                int node = queue.front();
                queue.pop();
                for (const auto& neigh : adjacency_list[node]) {
                    --degrees[neigh];
                    if (degrees[neigh] == 1 && !visited[neigh]) {
                        visited[neigh] = true;
                        queue.push(neigh);
                    }
                }
            }
            n -= len;
        }
        std::vector<int> ret;
        while (!queue.empty()) {
            ret.push_back(queue.front());
            queue.pop();
        }
        return ret;
    }
};
