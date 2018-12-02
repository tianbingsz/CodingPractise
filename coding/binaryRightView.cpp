/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
Solution:
for each level, find the rightmost elem, and push to the result array
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
// O(N), BST, beat 100%
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> right;
        deque<TreeNode*> queue;
        queue.push_back(root);
        while(!queue.empty()) { // queue for each level
            right.push_back(queue.back()->val);
            int nElem = queue.size();
            while (nElem > 0) {
                auto curNode = queue.front();
                queue.pop_front(); --nElem;
                if (curNode->left) {
                    queue.push_back(curNode->left);
                }
                if (curNode->right) {
                    queue.push_back(curNode->right);
                }
            }
        }
        return right;
    }
};
