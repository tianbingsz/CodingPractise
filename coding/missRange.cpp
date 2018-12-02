/*
Given a sorted integer array nums, where the range of elements are in the inclusive range [lower, upper], return its missing ranges.

Example:

Input: nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99,
Output: ["2", "4->49", "51->74", "76->99"]

*/
// https://leetcode.com/problems/missing-ranges/description/
// beat 100%, (start, end) move along the ordered nums
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        if (nums.empty()) return vector<string>{getRange(lower, upper)};
        vector<string> res;
        long start = (long) lower - 1;
        for (int i = 0; i <= nums.size(); ++i) {
            long end = (i == nums.size()) ? (long) upper + 1 : (long) nums[i];
            if (end - start >= 2) {
                // (start, end)
                res.push_back(getRange(start + 1, end - 1));
            }
            start = end;
        }
        return res;
    }
    
    string getRange(int start, int end){
        // [start , end]
        return (start == end) ? to_string(start) : 
            to_string(start) + "->" + to_string(end);
    }
        
};
