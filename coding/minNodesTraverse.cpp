/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/*
https://leetcode.com/discuss/interview-question/124861/digraph-cover-all-vertices-with-the-least-number-of-vertices
Given a directed graph G (can contain sub graphs and cycles), find the minimum number of vertices from which all nodes are reachable.
TO find the min coverage set of staring nodes, from each node int his cover set, we are able to visit every node.
For example:

Nodes:
    0, 1, 2, 3, 4, 5

Edges:
    1 <- 0
    0 <- 1 <- 2
    3 <- 1 <- 2
    2 <- 5
    4 <- 5

Representation:
    --> 4
  /
 5 --> 2 --> 1 <--> 0
              \
                --> 3
Matrix:
g = [[1, 1, 0, 0, 0, 0],
     [1, 1, 1, 0, 0, 0],
     [0, 0, 1, 0, 0, 1],
     [0, 1, 0, 1, 0, 0],
     [0, 0, 0, 0, 1, 1],
     [0, 0, 0, 0, 0, 1]]
Return 1 (node number 5). From node number 5 all other nodes are reachable.

If we remove edge 2 <- 5, the result is 2, because we need at least nodes number 5 and 2 to visit all nodes.

Representation of the graph if we remove the edge between nodes 2 and 5.

 5 --> 4

 2 --> 1 <--> 0
        \
          --> 3

Solution: DFS
I attempted to solve this problem by finding for every node j, and array of all nodes reachable from j. Basically, I did a DFS on every node, and the result looks like this:

{
    0: [True, True, False, True, False, False],
    1: [True, True, False, True, False, False],
    2: [True, True, True, True, False, False],
    3: [False, False, False, True, False, False],
    4: [False, False, False, False, True, False],
    5: [True, True, True, True, True, True]
}
This means that from node 0, I can reach nodes number 0, 1, 3. From node 1 I can reach nodes 0, 1 and 3. From node 5, I can reach all nodes.


*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <climits>
#include <cstdlib>
#include <string.h>


using namespace std;

class Solution {
public: 
    vector<int> getMinNodes(vector<vector<int>> &edges, int n) {
        for (const auto & e : edges) g[e[0]].push_back(e[1]);
        // cross different connected compoents
        vector<bool> gVisited(n, false);
        for (int s = 0; s < n; ++s) {
            if (gVisited[s]) continue;
            res.insert(s); // staring node
            // visited within a connected compoent
            unordered_set<int> visited;
            dfs(s, s, visited, gVisited);
        }    
        return vector<int>(res.begin(), res.end());
    }
    
private:
    unordered_set<int> res;
    unordered_map<int, vector<int>> g;
    
    // find a connected compoent starting from cur node
    void dfs(int s, int cur, unordered_set<int> &visited, 
            vector<bool> &gVisited) {
        visited.insert(cur);
        gVisited[cur] = true;
        for (int next : g[cur]) {
            if (gVisited[next]) {
                // this node can be reachable again, if not the  starting node,
                // we can remove it from result (if in the result)
                if (next != s) res.erase(next);
            }
            if (visited.count(next)) continue; // skip visited node
            dfs(s, next, visited, gVisited); // come to next
        }
    }
};


int main() {

    Solution sol;
    //vector<vector<int>> edges = {{0, 0}, {1, 2}, {2, 0}, {2, 3}, {3, 1}};
    //auto res = sol.getMinNodes(edges, 4);

	/* res: 1 */
    vector<vector<int>> edges = {{2, 9}, {3, 3}, {3, 5}, {3, 7}, {4, 8}, {5, 8}, {6, 6}, {7, 4}, {8, 7}, {9, 3}, {9, 6}};
    auto res = sol.getMinNodes(edges, 10);
    for (int n : res) {
        cout << n << ", ";
    }
    cout << endl;

	/*res: 2 0 1*/
    return 0;
}
