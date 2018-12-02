// https://leetcode.com/submissions/detail/172565057/
// https://leetcode.com/problems/binary-search/description/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int s = 0;
        int e = nums.size() - 1;
        while(s <= e) {
            int m = s + (e - s)/2;
            if (nums[m] == target) return m;
            if (nums[m] < target) {
                s = m + 1;
            } else {
                e = m - 1;
            }
        }
        return -1;
    }
};
