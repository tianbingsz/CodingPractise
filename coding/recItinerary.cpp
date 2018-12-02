/*
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
             But it is larger in lexical order.

Solution: DFS(s)
Graph {key => multiset} as might have duplication
    DFS(s):
        for (neigh : graph[s]):
            remove neigh from bucket graph[s]
            DFS(neigh)
        // finish expanding s and its children
        result.push_back(s) // in reverse visiting order
*/
// DFS, O(N), 16 ms
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        for (const auto & edge: tickets) {
            graph[edge.first].insert(edge.second);
        }
        dfs("JFK");
        return vector<string>(itiner.rbegin(), itiner.rend());
    }

private:
    vector<string> itiner;
    unordered_map<string, multiset<string>> graph;
    void dfs(const string& s) {
        while(!graph[s].empty()) {
            string next = *graph[s].begin();
            graph[s].erase(graph[s].begin());
            dfs(next);
        }
        itiner.push_back(s);
    }
};
