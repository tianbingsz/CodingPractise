/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example:

Input: 
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Output: ["eat","oath"]

*/
// use Trie to pruning, and check if the string find in board is at Trie
// 144 ms, O(MN), 25%
struct TrieNode {
    std::shared_ptr<TrieNode> children[26] = {nullptr};
    bool end {false};
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = std::make_shared<TrieNode>();
    }

    /** Inserts a word into the trie. */
    void insert(const string &word) {
        auto cur = root;
        for (char c : word) {
            int branch = c - 'a';
            if (cur->children[branch] == nullptr) {
                cur->children[branch] = std::make_shared<TrieNode>();
            }
            cur = cur->children[branch];
        }
        cur->end = true;
    }

    /** Returns if the word is in the trie. */
    bool search(const string &word) {
        auto cur = root;
        for (char c : word) {
            int branch = c - 'a';
            if (cur->children[branch] == nullptr) {
                return false;
            }
            cur = cur->children[branch];
        }
        return cur->end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string &prefix) {
        auto cur = root;
        for (char c : prefix) {
            int branch = c - 'a';
            if (cur->children[branch] == nullptr) {
                return false;
            }
            cur = cur->children[branch];
        }
        return true;
    }

private:
    std::shared_ptr<TrieNode> root;
};


class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty() || board[0].empty()) return {};

        for (const string &s : words) {
            trie.insert(s);
        }
        n = board.size();
        m = board[0].size();
        visited.assign(n, vector<bool>(m, false));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dfs(board, "", i, j);
            }
        }
        vector<string> strs(res.begin(), res.end());
        return strs;
    }

private:
    Trie trie;
    int n {0};
    int m {0};
    vector<vector<bool>> visited;
    unordered_set<string> res;
    void dfs(const vector<vector<char>>& board,
             string s, int x, int y) {
        if (x < 0 || x >=n || y < 0 || y >= m) return;
        if (visited[x][y]) return;
        s += board[x][y]; // include current char
        if (!trie.startsWith(s)) return; //pruning
        if (trie.search(s)) res.insert(s); // valid string
        // next candidate
        visited[x][y] = true; //mark visited
        dfs(board, s, x + 1, y);
        dfs(board, s, x, y + 1);
        dfs(board, s, x - 1, y);
        dfs(board, s, x, y - 1);
        visited[x][y] = false;
    }

};
