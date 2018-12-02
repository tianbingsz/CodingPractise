/*
Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

*/
// 8 ms, beat 99.73%
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        used.assign(nums.size(), false);
        vector<int> path;
        perm(nums, 0, path);
        return res;
    }

private:
    vector<vector<int>> res;
    vector<bool> used;
    void perm(const vector<int> &nums, int end,
              vector<int> &path) {
        if (nums.size() == end) {
            res.push_back(path); return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            // a perm(A[end+1, n]), pick a in available num in [1..n] and put on A[end]
            perm(nums, end + 1, path);
            path.pop_back();
            used[i] = false;
        }
    }
};

// backtracking, 12 ms
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        helper(nums, 0);
        return res;
    }

private:
    vector<vector<int>> res;

    void helper(vector<int> &nums, int end) {
        if (end == nums.size()) {
            res.push_back(nums); return;
        }
        for (int i = end; i < nums.size(); ++i) {
            std::swap(nums[i], nums[end]);
            // a perm(SA[end + 1...n]), a in [end ...n], 
            // and SA = Swap a with elem in A[end...n]
            helper(nums, end + 1);
            std::swap(nums[i], nums[end]);
        }
    }
};
