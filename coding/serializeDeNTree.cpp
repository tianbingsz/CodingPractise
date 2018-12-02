/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
// 68 ms, 82.62%
class Codec {
public:

    // Encodes a tree to a single string.
     string serialize(Node* root) {
        string s;
        encode_dfs(root, s);
        return s;
    }

    void encode_dfs(Node* root, string& s){
        if(!root) return;
        s += " " + to_string(root->val) + " " + to_string(root->children.size());
        for(auto p:root->children) encode_dfs(p, s);
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        stringstream ss(data);
        return decode(ss);
    }

    Node* decode(string data) {
        stringstream ss(data);
        return decode(ss);
    }

    Node* decode(stringstream& ss){
        // check end of file
        ss.peek();
        if(ss.eof()) return nullptr;
        Node* root = new Node();
        int child_size;
        ss >> root->val >> child_size;
        for(int i=0; i<child_size;i++) {
            root->children.push_back(decode(ss));
        }
        return root;
    }
};

// nullptr <==> "#", 68 ms, 82.62%
class Codec {
public:

    // Encodes a tree to a single string.
     string serialize(Node* root) {
        string s;
        encode_dfs(root, s);
        return s;
    }

    void encode_dfs(Node* root, string& s){
        if(root == nullptr) {
            s += "#"; return;
        }
        s += " " + to_string(root->val) + " " + to_string(root->children.size());
        for(auto p:root->children) encode_dfs(p, s);
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        stringstream ss(data);
        return decode(ss);
    }

    Node* decode(string data) {
        stringstream ss(data);
        return decode(ss);
    }

    Node* decode(stringstream& ss){
        string val;
        ss >> val;
        if (val == "#") return nullptr;
        Node* root = new Node();
        root->val = std::stoi(val);
        int child_size;
        ss >> child_size;
        for(int i=0; i<child_size;i++) {
            root->children.push_back(decode(ss));
        }
        return root;
    }
};
