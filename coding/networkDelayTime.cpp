/*
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

Solution: Dijstra Algo to find the max (or shortest in original) distance from src to all other nodes
Use Priority Queue pq to store {dist[u], u}
for the next v in neigh(u):
    if d[v] > d[u] + w(u, v):
       d[v] = d[u] + w(u, v)
       pq.push({d[v],v}) //update a bigger dist
*/
// Dijstra Algorithm
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        unordered_map<int, vector<pair<int, int>>> graph; // <u, {v, w}>
        for (const auto & t : times) {
            graph[t[0]].push_back({t[1], t[2]});
        }
        vector<int> dist(N + 1, INT_MAX);
        dist[K] = 0;
        // pair<d[u], u>
        priority_queue<pair<int, int>, vector<pair<int, int>>,
            std::greater<pair<int,int>>> pq;
        pq.push({0, K});
        while (! pq.empty()) {
            auto node = pq.top(); pq.pop();
            int u = node.second;
            for (const auto & neigh: graph[u]) {
                int v = neigh.first;
                int w = neigh.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w; // du + w(u,v)
                    pq.push({dist[v], v}); // update
                }
            }
        }
        int maxDelay = 0;
        for (int i = 1; i <=N; ++i) {
            maxDelay = std::max(maxDelay, dist[i]);
        }
        return maxDelay == INT_MAX ? -1 : maxDelay;
    }
};
