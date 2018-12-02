/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.

Solution:
Trie Prefix Tree
*/
struct TrieNode {
    std::shared_ptr<TrieNode> child[26] = {nullptr};  
    bool end {false};
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = std::make_shared<TrieNode>();    
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        auto cur = root;
        for (char c : word) {
            int branch = c - 'a';
            if (cur->child[branch] == nullptr) {
                cur->child[branch] = std::make_shared<TrieNode>();
            }
            cur = cur->child[branch];
        }
        cur->end = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return search(word, root, 0);   
    }

private:
    std::shared_ptr<TrieNode> root;
    
    // search word[start, end) from root cur
    bool search(string &word, std::shared_ptr<TrieNode> &cur, int start) {
        if (cur == nullptr) return false;
        if (start == word.size()) {
            return cur->end;
        }
        if (word[start] == '.') {
            for (auto next : cur->child) {
                if (search(word, next, start + 1)) return true;
            }
            return false; // not found
        } 
        auto next = cur->child[word[start] - 'a'];
        if (next == nullptr) return false;
        return search(word, next, start + 1);
    }
    
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
