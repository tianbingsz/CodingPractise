/*
Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

Example 1:

Input:
org: [1,2,3], seqs: [[1,2],[1,3]]

Output:
false

Explanation:
[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:

Input:
org: [1,2,3], seqs: [[1,2]]

Output:
false

Explanation:
The reconstructed sequence can only be [1,2].
Example 3:

Input:
org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]

Output:
true

Explanation:
The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input:
org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]

Output:
true
*/
// equivelent to check org is a topological sort of graph from seqs
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (org.empty() && seqs.empty())  return true;
        if (org.empty() || seqs.empty())  return false;
        int n = org.size();
        vector<int> inDegree(n+1, 0);
        Graph graph;
        int nEmpty = 0;
        for (const auto &s : seqs) {
            if (s.empty()) nEmpty++;
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] > n ||  s[i] < 0) return false;
                if (i < s.size() - 1 && !graph[s[i]].count(s[i+1])) {
                    if (s[i+1] > n || s[i+1] < 0) return false;
                    graph[s[i]].insert(s[i+1]); // a-> b
                    ++inDegree[s[i+1]];
                }
            }
        }
        if (nEmpty == seqs.size()) return false;
        // check topological sort
        for (int i = 0; i < n; ++i) {
            int cur = org[i];
            // if (graph.count(cur) == 0) return false;
            if (inDegree[cur] > 0 || (i < n -1 && inDegree[org[i+1]] == 0)) {
                return false; // first elem should have 0 in degree
            }
            for (const auto &next : graph[cur]) {
                if (inDegree[next] == 0) return false;
                --inDegree[next];
            }
        }
        return inDegree[org.back()] == 0;
    }
    
private:
    // {2 => {1}, 3 => {1, 2}} == [[1,2], [1,3], [2,3]]
    typedef unordered_map<int, unordered_set<int>> Graph;
};

