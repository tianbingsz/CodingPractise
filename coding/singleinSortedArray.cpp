/*
Given a sorted array consisting of only integers where every element appears twice except for one element which appears once. Find this single element that appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10

*/
// https://leetcode.com/submissions/detail/174694409/
// O(logn), binary search, find a range [s, leftE], [rightS,e] with odd number of elems
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        if (nums.empty() || nums.size() % 2 == 0) return 0;
        int s = 0, e = nums.size() - 1;
        // search in [s, e]
        while (s < e) {
            if (e == s + 1) {
                if (nums[s] == nums[e]) return 0;
                return nums[s];
            }
            // e - s >= 2, m - 1>= s, m + 1 <= e
            int m = s + (e - s) / 2; 
            int leftE = m; // [s, leftEnd]
            int rightS = m; // [rightS, e]
            if (nums[m] == nums[m - 1]) {
                leftE = m - 2; 
                rightS = m + 1;
            } else if (nums[m] == nums[m+1]) {
                leftE = m - 1;
                rightS = m + 2;
            } else {
                return nums[m];  
            }
            int leftLen = leftE - s + 1;
            int rightLen = e - rightS + 1;
            if (leftLen %2 == 1) {
                e = leftE;
            } else if (rightLen % 2 == 1) {
                s = rightS;
            }
        }
        return nums[e]; // s=e
    }
};
