/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.


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
// 4 ms, 100%
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        int height = -1;
        return dfs(root, height);    
    }
private:
    bool dfs(TreeNode *root, int &h) {
        if (root == nullptr) {
            h = 0; return true;
        }    
        int lh = 0, rh = 0;
        if (!dfs(root->left, lh)) return false;
        if (!dfs(root->right, rh)) return false;
        h = 1 + std::max(lh, rh);
        if (abs(lh - rh) > 1) return false;    
        return true;
    }
};
