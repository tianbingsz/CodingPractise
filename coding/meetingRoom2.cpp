/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2
Example 2:

Input: [[7,10],[2,4]]
Output: 1
Solution:
map m : <time, num of rooms needed>
1.for a meeting interval [start, end], if time come to start, we need to
add a room(++m[start]), if time come to end, we relase a room (--m[end])
2. sorted the time,
for t from early to finish:
    numRooms += m[t]
    maxRooms = max(numRooms[t] for t = 1 to n)
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
// O(NlogN), map is sorted, beat  99.76%
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> meetings;
        for (const auto & inter : intervals) {
            ++meetings[inter.start]; // start a new meeting
            --meetings[inter.end]; // end a meeting
        }
        int res = 0,  rooms = 0;
        for (const auto & it : meetings) {
            rooms += it.second;
            res = std::max(res, rooms);
        }
        return res;
    }
};
