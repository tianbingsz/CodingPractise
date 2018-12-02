/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

Example:

Input: nums = [3,5,2,1,6,4]
Output: One possible answer is [3,5,1,6,2,4]

Solution:
ordering: ...a > x < y > z < b....
if x > y, then swap(x, y), as prev a > x, after swapping, a > y, ordering keep
if y < z, then swap(y, z), similarly, after swapping, ordering keep
*/
// O(N)
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        if (nums.size() < 2) return;
        bool less = true;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (less) { // should n_i <= n_{i+1}
                if (nums[i] > nums[i+1]) {
                    std::swap(nums[i], nums[i + 1]);    
                }
            } else { // should n_i >= n_{i+1}
                if (nums[i] < nums[i+1]) {
                    std::swap(nums[i], nums[i+1]);    
                }   
            }  
            less = !less; // more than
        }
    }
};
