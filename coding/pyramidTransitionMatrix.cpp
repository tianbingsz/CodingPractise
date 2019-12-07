/*
We are stacking blocks to form a pyramid. Each block has a color which is a one letter string.

We are allowed to place any color block C on top of two adjacent blocks of colors A and B, if and only if ABC is an allowed triple.

We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.

Return true if we can build the pyramid all the way to the top, otherwise false.

Example 1:

Input: bottom = "BCD", allowed = ["BCG", "CDE", "GEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  G   E
 / \ / \
B   C   D

We are allowed to place G on top of B and C because BCG is an allowed triple.  Similarly, we can place E on top of C and D, then A on top of G and E.


Example 2:

Input: bottom = "AABA", allowed = ["AAA", "AAB", "ABA", "ABB", "BAC"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.

Solution:
https://www.cnblogs.com/grandyang/p/8476646.html

1. Build map<string, candidate>
AA=>AB, AB=>AB, BA=> C (eg.2)

2. cur level, above level
DFS(cur, above):
	if above is top level and cur the second top level: return true
	if above.len + 1 == cur.len, implies above level is filled full:
		move to up level, DFS(above, "")
	find the col = above.size
	for each c in candidate (map[cur.substr(col,2)])
		check if DFS(cur, above + c) TRUE: return true
	return false
*/

// 4 ms, 95.28%
class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (string &s : allowed) {
            // AAB : AA=>B
            matchCandidate[s.substr(0,2)].push_back(s[2]);
        }
        return dfs(bottom, "");
    }

private:
    unordered_map<string, string> matchCandidate;

    bool dfs(string cur, string above) {
        // first level and second level filled
        if (above.size() == 1 && cur.size() == 2) return true;
        if (above.size() == cur.size() - 1) { // up level
            return dfs(above, "");
        }
        // go to next column in above level
        int col = above.size();
        string candidate = matchCandidate[cur.substr(col, 2)];
        for (char c : candidate) {
            if (dfs(cur, above + c)) return true;
        }
        return false;
    }
};
