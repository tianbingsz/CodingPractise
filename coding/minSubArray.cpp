/*
Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example:

Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.

Solution: Two Pointers, sliding window
A[l,r], sum = sum of A[l,r] 
if sum < s, expand sum += A[r], ++r
else, update mlen = min(mlen, r - l +1) and shrink the window, sum -= A[l], ++l
*/
// https://leetcode.com/problems/minimum-size-subarray-sum/description/
// https://leetcode.com/submissions/detail/172777129/
// sliding window O(N)
// 8 ms, 98.60%, O(N)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int sum = 0;
        int mlen = INT_MAX;
        int l = 0;
        for (int r = 0; r < nums.size(); ++r) {
            sum += nums[r];
            while (sum >= s) { // shrink
                mlen = std::min(mlen, r - l + 1);
                sum -= nums[l]; ++l;
            }
        }
        return mlen == INT_MAX ? 0 : mlen;
    }
};
