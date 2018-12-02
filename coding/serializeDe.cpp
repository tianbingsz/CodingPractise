/*
449. Serialize and Deserialize BST

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
Solution:
encode: travese BST in pre-order, append each val to string code with compression (memcpy, 4 bytes for each val)
decode: pre-order travesal, reconstruct the BST with idx for each val from code vector,
use memcpy to read each node val
idx is ordering with pre-order
*/
// O(N), DFS pre-order
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string code;
        inOrder(root, code);
        return code;
    }
    
    void inOrder(TreeNode* root, string& code) {
        if (root == nullptr) return;
        char buf[4];
        std::memcpy(buf, &(root->val), sizeof(int)); //burn the int into 4 chars
        for (int i=0; i< 4; i++) code.push_back(buf[i]);
        inOrder(root->left, code);
        inOrder(root->right, code);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int idx = 0;
        return reconstructBST(data, idx, INT_MIN, INT_MAX);
    }
    
    inline TreeNode* reconstructBST(const string& code, int& idx, int minValue, int maxValue) {
        //using pos to check whether buffer ends is better than using char* directly.
        if (idx >= code.size()) return nullptr; 
        
        int value;
        std::memcpy(&value, &code[idx], sizeof(int));
        if (value < minValue || value > maxValue) return nullptr;
        
        TreeNode* root = new TreeNode(value);
        idx += sizeof(int);
        root->left = reconstructBST(code, idx, minValue, value);
        root->right = reconstructBST(code, idx, value, maxValue);
        return root;
    }
};
