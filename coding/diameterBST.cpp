/*
Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].


*/
// https://leetcode.com/problems/diameter-of-binary-tree/description/
/*
 traverse every node to get max of leftDepth, then rightDepth, then add those 2
 at every node, calculate the max depth by helper
*/
// O(N), beat 100%
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int height = 0;
        return diameterHelper(root, height);
    }
    
    int diameterHelper(TreeNode* root, int &height) {
        if (root == nullptr) return 0;
        int leftHeight = 0;
        int rightHeight = 0;
        int lmeter = diameterHelper(root->left, leftHeight);
        int rmeter = diameterHelper(root->right, rightHeight);
        // record the height from root
        height = 1 + std::max(leftHeight, rightHeight);
        return std::max(leftHeight + rightHeight, /*pass root*/
                       std::max(lmeter, rmeter)/*no pass root*/);
    }
};

// slower, 5%
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftRootPath = rootPathLen(root->left);
        int rightRootPath = rootPathLen(root->right);
        return std::max(leftRootPath + rightRootPath, 
                        std::max(diameterOfBinaryTree(root->left),
                                diameterOfBinaryTree(root->right)));
    }
    
    int rootPathLen(TreeNode* root) {
        if (root == nullptr) return 0;
        return 1 + std::max(rootPathLen(root->left), rootPathLen(root->right));
    }
};
