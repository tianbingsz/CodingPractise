/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/*
boggle game，给一个board和字典，找出board上出现最多的单词集合，单词不能重叠在同一个位置

例如

board:
{'a', 'b', 'c'},
{'d', 'e', 'f'},
{'g', 'h', 'i'}

dict:
["abc", "cfi", "beh", "defi", "gh"]
答案应该是 ["abc", "defi", "gh"]

分析
这个题和 Leetcode 的 Word Search II 有点像，唯一区别是这个题里面 board 上的单词不可以重复利用。刚开始我觉得可以 run 一次 Word Search II 得到所有的可能单词先，然后求最大的一个单词无重合集合，但是找无重合集合这个又变成一个 subset 的题目（我没有研究更快的方法）。所以最后还是考虑用控制一下递归搜索的条件，在找单词的时候记录一下已经选中的单词，只是这个过程需要两层递归。

还是用一个 Trie 来加速 Word 的查找
第一个循环，遍历 board 上每一个点，然后从这里找第一个单词（因为第一个单词的选择会影响最终单词数量），开始第一个递归。
第一个递归的作用是，从当前点开始，通过第二个递归拿到当前点可行的每一个单词。挨个放入，每放入一个更新当前 board 的使用情况，然后开始下一层搜索。
第二个递归的作用是，从当前点开始，找所有可行的单词 indexes，为第一个递归提供选择
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;

class Solution {
public:
    struct TrieNode {
        shared_ptr<TrieNode> children[26] = {nullptr};
        bool end{false};
    };

    vector<string> getAllWords(const vector<vector<char>> &board,
        const vector<string>& dict) {
        // build Trie dict
        root = make_shared<TrieNode>();
        for (const auto &s : dict) {
            add(s);
        }
        // for each starting pos (i,j), find the largest num of words
        int n = board.size(), m = board[0].size();
        vector<string> res; // most strings at board
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                vector<vector<bool>> visited(n, vector<bool>(m, false));
                // max num of words in the board (from dict) starting from (i,j)
                vector<string> words;
                findWords(board, i, j, words, visited, res);
            }
        }
        return res;
    }


private:
    shared_ptr<TrieNode> root;

    void findWords(const vector<vector<char>> &board, int x, int y,
        vector<string> &words, vector<vector<bool>> &visited,
        vector<string> &res) {
        int n = board.size(), m = board[0].size();
        // starting from (x,y), try to add words ...
        for (int i = x; i < n; ++i) {
            for (int j = y; j < m; ++j) {
                if (visited[i][j]) continue;

                vector<vector<int>> wSeq;
                vector<int> path;
                // find all available word seq starting from (i,j)
                getNextWSeq(board, visited, root, wSeq, path, i, j);
                for (const auto &wIdx : wSeq) {
                    // try candidate word
                    string word;
                    for (int idx : wIdx) {
                        int row = idx / m, col = idx % m;
                        word += board[row][col];
                        visited[row][col] = true;
                    }
                    words.push_back(word);
                    cout << "add word: " << word << endl;
                    if (words.size() > res.size()) {
                        for (string &s : words) {
                            res.push_back(s);
                        }
                    }
                    findWords(board, i, j, words, visited, res);
                    for (int idx : wIdx) {
                        int row = idx / m, col = idx % m;
                        visited[row][col] = false;
                    }
                    words.pop_back();
                }
            }
            y = 0; // next row y starting from 0
        }
    }

    // DFS, find all available words seq from (x,y) in dict
    void getNextWSeq(const vector<vector<char>> &board,
        vector<vector<bool>> &visited, shared_ptr<TrieNode> &cur,
        vector<vector<int>> &wSeq, vector<int> &path, int x, int y) {
        int n = board.size(), m = board[0].size();
        if (x < 0 || x == n || y < 0 || y ==m) return;
        if (visited[x][y] || cur->children[board[x][y] - 'a'] == nullptr) return;
        cur = cur->children[board[x][y] - 'a']; // available branch
        visited[x][y] = true;
        path.push_back(x * m + y);
        if (cur->end) {
            // find a word, add its position path to wSeq
            wSeq.push_back(path);
            return;
        }
        // add char(x,y) and try neighs
        getNextWSeq(board, visited, cur, wSeq, path, x + 1, y);
        getNextWSeq(board, visited, cur, wSeq, path, x - 1, y);
        getNextWSeq(board, visited, cur, wSeq, path, x, y + 1);
        getNextWSeq(board, visited, cur, wSeq, path, x, y - 1);
        path.pop_back();
        visited[x][y] = false;
    }

    // add word in Trie
    void add (const auto &s) {
        auto cur = root;
        for (char c : s) {
            if (cur->children[c - 'a'] == nullptr) {
                cur->children[c - 'a'] = make_shared<TrieNode>();
            }
            cur = cur->children[c - 'a'];
        }
        cur->end = true;
    }
};


int main()
{
    vector<vector<char>>  board = {
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'}
    };

    vector<string> dict = {
        "abc", "cfi", "beh", "defi", "gh"
    };

    Solution sol;
    auto res = sol.getAllWords(board, dict);
    for (const auto &s : res) cout << s << endl;

    /* "abc", "defi", "gh"*/
    return 0;
}

