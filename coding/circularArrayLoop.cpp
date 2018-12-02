/*
You are given an array of positive and negative integers. If a number n at an index is positive, then move forward n steps. Conversely, if it's negative (-n), move backward n steps. Assume the first element of the array is forward next to the last element, and the last element is backward next to the first element. Determine if there is a loop in this array. A loop starts and ends at a particular index with more than 1 element along the loop. The loop must be "forward" or "backward'.

Example 1: Given the array [2, -1, 1, 2, 2], there is a loop, from index 0 -> 2 -> 3 -> 0.

Example 2: Given the array [-1, 2], there is no loop.

Note: The given array is guaranteed to contain no element "0".

Can you do it in O(n) time complexity and O(1) space complexity?

*/
// https://leetcode.com/problems/circular-array-loop/
// http://www.cnblogs.com/grandyang/p/7658128.html
// Two pointers O(N), beat 100%
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        if (nums.size() < 2) return false;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int slow = i, fast = i, step = 0;
            do {
                if (nums[slow] * nums[nextIdx(n, slow, nums[slow])] < 0) {
                    break; //in different direction, loop should be in one direction
                }
                slow = nextIdx(n, slow, nums[slow]);
                fast = nextIdx(n, fast, nums[fast]);
                fast = nextIdx(n, fast, nums[fast]);
                step ++;
            } while(slow != fast);
            if (step > 1) return true;
        }
        return false;
    }
    
    // get next idx
    int nextIdx(int n, int idx, int d) {
        int next = idx + d;
        return next > 0 ? next % n : (n + next) % n;
    }
};
