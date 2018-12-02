/*
Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
Solution: pre-order traversal
1. Create a dumy Node and global pointer tail = &dumy
2. preOrder (root):
    // tail connect to next node root in pre-order
    tail->right = root, tail = root
    root->left = nullptr, root->right = nullptr, clear pointers
    preOrder(left)
    preOrder(right)
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
// 4 ms, 100%, O(N)
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode dumy(INT_MIN);
        tail = &dumy;
        preOrder(root);
    }
private:
    TreeNode *tail = nullptr;
    void preOrder(TreeNode* root) {
        if (root == nullptr) return;
        auto left = root->left;
        auto right = root->right;
        root->left = nullptr; root->right = nullptr;
        tail->right = root;
        tail = root;
        preOrder(left);
        preOrder(right);
    }
};
