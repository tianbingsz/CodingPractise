/*
Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#'). For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed. Here are the specific rules:

The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
If less than 3 hot sentences exist, then just return as many as you can.
When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
Your job is to implement the following functions:

The constructor function:

AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data. Sentences is a string array consists of previously typed sentences. Times is the corresponding times a sentence has been typed. Your system should record these historical data.

Now, the user wants to input a new sentence. The following function will provide the next character the user types:

List<String> input(char c): The input c is the next character typed by the user. The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). Also, the previously typed sentence should be recorded in your system. The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.


Example:
Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2]) 
The system have already tracked down the following sentences and their corresponding times: 
"i love you" : 5 times 
"island" : 3 times 
"ironman" : 2 times 
"i love leetcode" : 2 times 
Now, the user begins another search: 

Operation: input('i') 
Output: ["i love you", "island","i love leetcode"] 
Explanation: 
There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored. 

Operation: input(' ') 
Output: ["i love you","i love leetcode"] 
Explanation: 
There are only two sentences that have prefix "i ". 

Operation: input('a') 
Output: [] 
Explanation: 
There are no sentences that have prefix "i a". 

Operation: input('#') 
Output: [] 
Explanation: 
The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search. 


*/
// Tire
struct TrieNode {
    shared_ptr<TrieNode> child[27] = {nullptr}; 
    int cnt{0};
    string path;
    bool end{false};
};

struct cmp {
    bool operator() (const pair<int, string> &a, const pair<int, string> &b) {
        return (a.first < b.first) || (a.first == b.first && a.second > b.second);
    }    
};

class Trie {
public:
    Trie() {
        root = make_shared<TrieNode>();
    }
    
    void insert(const string &s, int num) {
        auto cur = root;
        for (char c : s) {
            int b = idx(c);
            if (cur->child[b] == nullptr) {
                cur->child[b] = make_shared<TrieNode>();
            }
            cur = cur->child[b];
        }
        cur->cnt = num;
        cur->path = s;
        cur->end = true;
    }
    
    priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> query(const string &prefix) {
        auto cur = root;
        for (char c : prefix) {
            int b = idx(c);
            if (cur->child[b] == nullptr) {
                return {};   
            }
            cur = cur->child[b];
        }
        priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> res;  
        dfs(prefix, cur, res);
        return res;
    }
    
    /*find the all the strings starting from prefix*/
    void dfs(string path, shared_ptr<TrieNode> &cur, 
             priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> &q) {
        if (cur->end > 0) {
            q.push({cur->cnt, path});  
        } 
        for (char c = 'a'; c <= 'z'; ++c) {
            if (cur->child[idx(c)]) {
                dfs(path + c, cur->child[idx(c)], q);
            }
        }
        if (cur->child[26]) {
            dfs(path + ' ', cur->child[26], q);
        }
    }
    
private:
    shared_ptr<TrieNode> root;
    int idx(char c) {
        return (c == ' ') ? 26 : c - 'a';
    }
};

class AutocompleteSystem {
public:
    AutocompleteSystem(vector<string> sentences, vector<int> times) {
        for (int i = 0; i < times.size(); ++i) {
            trie.insert(sentences[i], times[i]);
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            trie.insert(word, 1);
            word = "";
            return {};
        }
        word += c;
        auto q = trie.query(word);
        if (q.empty()) return {};
        vector<string> res;
        for (int i = 0; i < std::min((int)q.size(), 3); ++i) {
            res.push_back(q.top().second); q.pop();
        }
        return res;
    }
private:
    Trie trie;
    string word;
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj.input(c);
 */