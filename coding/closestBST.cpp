// https://leetcode.com/problems/closest-binary-search-tree-value/description/
// https://leetcode.com/submissions/detail/172783273/

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
    int closestValue(TreeNode* root, double target) {
        double dist = std::numeric_limits<double>::max();
        int res = 0;
        helper(root, target, dist, res);
        return res;
    }  
    
    // traversal the BST to find the min distance node 
    void helper(TreeNode* root, double target, double &minDist, int &res) {
        if (root == NULL) return;
        double rootDist = abs(root->val - target);
        if (rootDist < minDist) {
            minDist = rootDist; res = root->val;
        }
        helper(root->left, target, minDist, res);
        helper(root->right, target, minDist, res);
    }    
};


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
    int closestValue(TreeNode* root, double target) {
        if (root == NULL) return INT_MAX;
        if (root->left == NULL && root->right == NULL) 
            return root->val;
        int leftVal = closestValue(root->left, target);
        int rightVal = closestValue(root->right, target);
        double rootDist = abs(root->val - target);
        double leftDist = abs(leftVal - target);
        double rightDist = abs(rightVal - target);
        if (rootDist < leftDist && rootDist < rightDist) {
            return root->val;
        }
        if (leftDist < rightDist && leftDist < rootDist) {
            return leftVal;    
        }
        if (rightDist < leftDist && rightDist < rootDist) {
            return rightVal;    
        }
    }  
};
