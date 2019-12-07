/*
There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.

Now given all the cities and fights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
Solution: BFS
Keep mDist = dist[dst]: dist from src to dst, init INT_MAX
One Step BFS Traversal:
traverse current node (cur) from src, for the neighbor next, update the dist to src as:
dist[next] = dist[cur] + d(cur, next), if dist[next] > mDist, prune it, 
if next is dst, update mDist = min(mDist, dist[next])
step + 1
if step > K, stop
*/
// BFS, beat 92.97%
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        // {u => vector{v, cost(u,v)}}
        unordered_map<int, vector<pair<int, int>>> graph;
        for (const auto & flight : flights) {
            graph[flight[0]].push_back({flight[1], flight[2]});
        }
        queue<pair<int, int>> q; // {node, dist(src->node)}
        q.push({src, 0});
        int mDist = INT_MAX;
        int step = 0;
        while(! q.empty()) {
            int qSize = q.size();
            for (int i = 0; i < qSize; ++i) {
                int node = q.front().first;
                int dist = q.front().second;
                q.pop();
                if (node == dst)
                    mDist = std::min(mDist, dist);
                for (const auto & neigh : graph[node]) {
                    // pruning neighbor with large dist
                    if (dist + neigh.second > mDist) continue;
                    // dist[v] = dist[u] + weight(u,v)
                    q.push({neigh.first, dist + neigh.second});
                }
            }
            if (step++ > K) break;
        }
        return mDist == INT_MAX ? -1 : mDist;
    }
};

// 8 ms
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int, vector<pair<int,int>>> g; // <u => {v, w}>
        for (const auto & f : flights) {
            g[f[0]].emplace_back(f[1], f[2]);
        }
        queue<pair<int,int>> q; // <u, d[u]>
        q.push({src, 0});
        vector<int> d(n, INT_MAX); d[src] = 0;
        int mDist = INT_MAX;
        int step = 0;
        while(! q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto cur = q.front(); q.pop();
                int node = cur.first;
                int du = cur.second;
                if (node == dst) mDist = min(mDist, du);
                for (const auto &next : g[node]) {
                    //if (du + next.second > mDist) continue;
                    // d[v] = d[u] + w(u,v)
                    if (d[next.first] > du + next.second) {
                        d[next.first] = du + next.second;
                        q.push({next.first, d[next.first]});
                    }
                }
            }
            if (step++ > K) break;
        }
        return mDist == INT_MAX? -1 : mDist; 
    }
};
