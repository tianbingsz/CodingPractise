/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

Example 1:

Input: [[0,30],[5,10],[15,20]]
Output: false
Example 2:

Input: [[7,10],[2,4]]
Output: true

Solution:
1. Sort the intervals with the first starting time
2. for each interval:
    if it is conflicts with the previous intervals, conflicts
otherwise, return true
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
// O(NlogN), beat 99.89%
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), compare);
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start < intervals[i-1].end) return false;
        }
        return true;
    }
private:
    bool static compare(const Interval &x, const Interval &y) {
        return x.start < y.start;
    }
};

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
    bool canAttendMeetings(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), 
                 [](const Interval &x, const Interval &y) {
                     return x.start < y.start;});
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start < intervals[i-1].end) return false;
        }
        return true;
    }
};
