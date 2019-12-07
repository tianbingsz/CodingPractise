/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Example 1:

Input: pattern = "abab", str = "redblueredblue"
Output: true
Example 2:

Input: pattern = pattern = "aaaa", str = "asdasdasdasd"
Output: true
Example 3:

Input: pattern = "aabb", str = "xyzabcxzyabc"
Output: false
我们还是需要用哈希表来建立模式字符和单词之间的映射，我们还需要用变量p和r来记录当前递归到的模式字符和单词串的位置，在递归函数中，如果p和r分别等于模式字符串和单词字符串的长度，说明此时匹配成功结束了，返回ture，反之如果一个达到了而另一个没有，说明匹配失败了，返回false。如果都不满足上述条件的话，我们取出当前位置的模式字符，然后从单词串的r位置开始往后遍历，每次取出一个单词，如果模式字符已经存在哈希表中，而且对应的单词和取出的单词也相等，那么我们再次调用递归函数在下一个位置，如果返回true，那么我们就返回true。反之如果该模式字符不在哈希表中，我们要看有没有别的模式字符已经映射了当前取出的单词，如果没有的话，我们建立新的映射，并且调用递归函数，注意如果递归函数返回false了，我们要在哈希表中删去这个映射

*/

// 172 ms
class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        return dfs(pattern, 0, str, 0);
    }

private:
    unordered_map<char, string> m; // <a, red>

    bool dfs(const string &pat, int p, const string &str, int r) {
        if (p == pat.size() && r == str.size()) return true;
        if (p == pat.size() || r == str.size()) return false;
        char c = pat[p];
        for (int i = r; i < str.size(); ++i) {
            // candidate substr as pattern
            string t = str.substr(r, i - r + 1);
            if (m.count(c) && m[c] == t) {
                // match c to a pattern t str[r, i]
                if (dfs(pat, p+1, str, i+1)) return true;
            }
            if (m.count(c) == 0) {
                bool b = false;
                for (const auto &it : m) {
                    if (it.second == t) {
                        b = true; break;
                    }
                }
                if (!b) { // not find pattern t, add to map
                    m[c] = t;
                    if (dfs(pat, p+1, str, i+1)) return true;
                    m.erase(c);
                }
            }
        }
        return false;
    }
};
