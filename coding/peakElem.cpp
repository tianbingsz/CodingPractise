/*
A peak element is an element that is greater than its neighbors.

Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that nums[-1] = nums[n] = -∞.

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5
Explanation: Your function can return either index number 1 where the peak element is 2,
             or index number 5 where the peak element is 6.

Solution:
if nums[i-2] < nums[i-1] > nums[i] return i -1
*/
// O(N), 4 ms, 99.33%
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // n[-1] = -infty so assume nums[i-1] > nums[i-2], for i >=1
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i-1] > nums[i]) return i-1;
        }
        // as nums[n-2] < nums[n-1] < -infty
        return nums.size() - 1;
    }
};

// O(logN), 4 ms, 99.33%
/*
Solution: Binary Search
https://blog.csdn.net/NK_test/article/details/49926229
Binary(l, r)
    if l == r: return l
    in the range [l, r]:
        m1 = l + (r - l)/2
        m2 = m1 + 1
        if (A[m1] > A[m2]):
        // there exist a peak in [l, m1]
            Binary(l, m1)
        else: // exist a peak in [m2, r]
            Binary(m2, r)
*/
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int m1 = left + (right - left)/2;
            int m2 = m1 + 1;
            if (nums[m1] > nums[m2]) {
                // there is a peak in left half
                right = m1;
            } else { // a peak in right half
                left = m2;
            }
        }
        return left;
    }
};
