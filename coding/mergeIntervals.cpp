/*
56. Merge Intervals
Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considerred overlapping.

Solution:
Time O(NlogN)
1. sort intervals based on start
2. for each interval, either add into res list, or merge with the last interval in res list. 
*/
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(),
                 [](const Interval &i1, const Interval &i2) {
                     return i1.start < i2.start;
                 });
        vector<Interval> res;
        for (const auto & inter: intervals) {
            if (res.empty() || res.back().end < inter.start) {
                res.push_back(inter);
            } else { // merge [s1, e1] [s2, e2], e1 >= s2, s1 <= s2
                res.back().end = std::max(res.back().end, inter.end);    
            }
        }
        return res;
    }
};
