/*
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7
Solution:
Travesal node with binary search, find a node with the same value as key,
To delete this subtree rooted from node,
1) if this subtree is single noded, delete the root, return nullptr
2) if this subtree is only has one branch from this root, delete root, return the branch
3) if this subtree has two branches,
    find the smallest val node on the right sub-tree,
    replace this val to root's val to keep BST ordering
    delete this replace node in the right sub-tree
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
// beat 99%, O(logN)
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (key < root->val) { // delete node in left tree
            root->left = deleteNode(root->left, key);
            return root;
        }
        if (key > root->val) { // delete in right tree
            root->right = deleteNode(root->right, key);
            return root;
        }
        // key == val, delete root, take of 3 cases
        if (root->left == nullptr && root->right == nullptr) {
            return nullptr; // 1) delete single root
        }
        if (root->left == nullptr || root->right == nullptr) {
            // 2) delete root, return either left or right sub-tree
            return root->left ? root->left : root->right;
        }
        // 3) root has two vaild subtrees
        auto replace = root->right; // find the smallest node in right
        while(replace->left) replace = replace->left;
        root->val = replace->val;// replace root's val
        // delete replace node in the right tree
        root->right = deleteNode(root->right, replace->val);
        return root;
    }
};
