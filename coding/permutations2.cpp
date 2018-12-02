/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

Example:

Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
Solution:
during the swapping the nums[start] with nums[start...end],
if we find a duplicated num, skip it
*/
// beat 99.72%
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        perm(nums, 0);
        return res;
    }

private:
    vector<vector<int>> res;
    void perm(vector<int> &nums, int start) {
        if (start == nums.size()) {
            res.push_back(nums); return;
        }
        unordered_set<int> visited;
        for (int i = start; i < nums.size(); ++i) {
            if (visited.count(nums[i])) continue; // skip duplicated
            visited.insert(nums[i]);
            std::swap(nums[i], nums[start]);
            perm(nums, start + 1);
            std::swap(nums[i], nums[start]);
        }
    }
};
