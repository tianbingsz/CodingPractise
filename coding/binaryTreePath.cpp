/*
Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3
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
// O(N), beat 99%
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        string path;
        pathHelper(root, path);
        return res;
    }

    void pathHelper(TreeNode* root, string path) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr) {
            path += std::to_string(root->val);
            res.push_back(path);
            return;
        }
        path += std::to_string(root->val);
        path += "->";
        pathHelper(root->left, path);
        pathHelper(root->right, path);
    }

private:
    vector<string> res;
};
