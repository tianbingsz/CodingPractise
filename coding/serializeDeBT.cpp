/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example:

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
Solution:
Serialize:
PreOrder, travese each node val and insert into ostringstream out << to_string(val) + ' ',
if nullptr, insert "# " into out
Deserialize:
read each string (seperate with ' ') from istringstream in,
and if ecount "#", return nullptr, if valid val, create a root(val),
root->left = string[from next word from in]
root->right = string[from next word from in]
as istringstream in is alwasy moving forward word by word (sepreate by ' ')
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 20 ms
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream code;
        preOrderEncode(root, code);
        return code.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return preOrderDecode(in);
    }

private:
    void preOrderEncode(TreeNode* root, ostringstream &out) {
        if (root == nullptr) {
            out << "# ";
            return;
        }
        out << std::to_string(root->val) << ' ';
        preOrderEncode(root->left, out);
        preOrderEncode(root->right, out);
    }

    TreeNode* preOrderDecode(istringstream &in) {
        string val;
        in >> val;
        if (val == "#") return nullptr; // NULL

        auto root = new TreeNode(std::stoi(val));
        root->left = preOrderDecode(in); // next word
        root->right = preOrderDecode(in);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
