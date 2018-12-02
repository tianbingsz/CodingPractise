/*
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1

*/
// 4 ms
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> nSet;
        int mNum = 0;
        for (int num : nums) {
            if (num <= 0) continue;
            nSet.insert(num);
            mNum = max(mNum, num);
        }
        for (int i = 1; i <= mNum; ++i) {
            if (nSet.count(i) == 0) return i;
        }
        return mNum + 1;
    }
};

// O(N), 4 ms
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }
};
