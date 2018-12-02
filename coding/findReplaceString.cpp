/*
To some string S, we will perform some replacement operations that replace groups of letters with new ones (not necessarily the same size).

Each replacement operation has 3 parameters: a starting index i, a source word x and a target word y.  The rule is that if x starts at position i in the original string S, then we will replace that occurrence of x with y.  If not, we do nothing.

For example, if we have S = "abcd" and we have some replacement operation i = 2, x = "cd", y = "ffff", then because "cd" starts at position 2 in the original string S, we will replace it with "ffff".

Using another example on S = "abcd", if we have both the replacement operation i = 0, x = "ab", y = "eee", as well as another replacement operation i = 2, x = "ec", y = "ffff", this second operation does nothing because in the original string S[2] = 'c', which doesn't match x[0] = 'e'.

All these operations occur simultaneously.  It's guaranteed that there won't be any overlap in replacement: for example, S = "abc", indexes = [0, 1], sources = ["ab","bc"] is not a valid test case.

Example 1:

Input: S = "abcd", indexes = [0,2], sources = ["a","cd"], targets = ["eee","ffff"]
Output: "eeebffff"
Explanation: "a" starts at index 0 in S, so it's replaced by "eee".
"cd" starts at index 2 in S, so it's replaced by "ffff".
Example 2:

Input: S = "abcd", indexes = [0,2], sources = ["ab","ec"], targets = ["eee","ffff"]
Output: "eeecd"
Explanation: "ab" starts at index 0 in S, so it's replaced by "eee". 
"ec" doesn't starts at index 2 in the original S, so we do nothing.
Notes:

0 <= indexes.length = sources.length = targets.length <= 100
0 < indexes[i] < S.length <= 1000
All characters in given inputs are lowercase letters.
 
Solution:
init: res = S[0, idx[0]) 
for each sorted idx, [s, e), s = idx[i], e = idx[i+1] or S.size
1. if S[s, e) contains substr, replace with replacestr, append the left str : S[s, e) - substr 
    res += replacstr, res+= S[s,e) - substr if exists
2. if S[s, e) not contain substr, just add : res += S[s, e)
*/
// 98% beat, Time O(M), Space O(M + N), N is |S|, M is the size of indexes
class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        if (S.empty()) return "";
        // <idx, (src, replace)>, sorted by idx
        map<int, pair<string, string>> imap; 
        for (int i = 0; i < indexes.size(); ++i) {
            imap[indexes[i]] = {sources[i], targets[i]}; 
        }
        vector<int> sortedIdx;
        for (const auto & ent : imap) {
            sortedIdx.push_back(ent.first);
        }
        string res;
        if (!imap.empty() && sortedIdx[0] > 0) { //[0, idx1)
            res += S.substr(0, sortedIdx[0]);
        }
        for (int i = 0; i < sortedIdx.size(); ++i) {
            int s = sortedIdx[i];  
            int e = (i == sortedIdx.size() - 1) ? S.size() : sortedIdx[i+1];
            string src = imap[s].first;
            if (S.substr(s, e - s).find(src) == string::npos) {
                res += S.substr(s, e -s); // can not replace
                continue;
            }
            res += imap[s].second; // replace
            if (e - s > src.length()) 
                res += S.substr(s, e - s).erase(0, src.length());
        }
        return res;
    }
};
