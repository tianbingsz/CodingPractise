// https://leetcode.com/problems/next-closest-time/description/
// https://leetcode.com/submissions/detail/173585887/
// O(1440)
/*
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.

Solution:
current time is m mins, m = 60 * hours + mins
for i = 1 to 1440 (in the next day):
    find a valid time next
    next = (m + 1) % 1440 and all next = hg:ml, {hgml} in the old digits of m
*/
class Solution {
public:
    string nextClosestTime(string time) {
        vector<int> mins = {600, 60, 10, 1};
        auto colon = time.find(':');
        int cur = 60 * stoi(time.substr(0, colon)) + stoi(time.substr(colon + 1));
        string next = "0000";
        int d = 0;
        for (int i = 1; i <= 1440; ++i) {
            int m = (cur + i) % 1440;
            for (d = 0; d < 4; ++d) {
                next[d] = '0' + m / mins[d];
                m %= mins[d];
                if (time.find(next[d]) == std::string::npos) break;
            }
            if (d == 4) break; // find the next time
        }
        return next.substr(0, 2) + ':' + next.substr(2, 2);
    }
};
