/*
We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.

Find the total area covered by all rectangles in the plane.  Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:

Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: As illustrated in the picture.
Example 2:

Input: [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.

Solution:
For each y, collect the intervals ,  calc the sum of intervals
思路：二维转一维：扫描y轴，遍历每个y范围，然后求出与改y范围有相交的x范围，merge这些x的interval
*/
class Solution(object):
    def rectangleArea(self, rectangles):
        # Populate events
        OPEN, CLOSE = 0, 1
        events = []
        for x1, y1, x2, y2 in rectangles:
            events.append((y1, OPEN, x1, x2))
            events.append((y2, CLOSE, x1, x2))
        events.sort()

        def query():
            ans = 0
            cur = -1
            for x1, x2 in active:
                cur = max(cur, x1)
                ans += max(0, x2 - cur)
                cur = max(cur, x2)
            return ans

        active = []
        cur_y = events[0][0]
        ans = 0
        for y, typ, x1, x2 in events:
            # For all vertical ground covered, update answer
            ans += query() * (y - cur_y)

            # Update active intervals
            if typ is OPEN:
                active.append((x1, x2))
                active.sort()
            else:
                active.remove((x1, x2))

            cur_y = y

        return ans % (10**9 + 7)

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        if(rectangles.empty()) return 0;
        // y1 => {(x1, x2), open}, y2=>{(x1, x2), close}
        map<int, vector<vector<int>>> events;
        for (const auto & r : rectangles) {
            int x1 = r[0], x2 = r[2];
            int y1 = r[1], y2 = r[3];
            events[y1].push_back({x1, x2, 0}); // open
            events[y2].push_back({x1, x2, 1}); // close
        }

        set<pair<int, int>> activeXs; // default sort by first
        long long area = 0;
        int preY = events.begin()->first;
        for (const auto & e : events) {
            int y = e.first;
            area +=  calcArea(activeXs) * (y - preY);
            for (const auto & xs : e.second) { // intervals
                if (xs[2] == 0) { // open, add x intervals
                    activeXs.insert({xs[0], xs[1]});
                } else {
                    activeXs.erase({xs[0], xs[1]});
                }
            }
            preY = y;
        }
        return (int) area % ((int) (1e9 + 7));
    }
private:
    int calcArea(const set<pair<int, int >>& activeXs) {
        int area = 0;
        int cur = -1;
        for (const auto & e : activeXs) {
            cur = std::max(cur, e.first);
            area += std::max(0, e.second - cur);
            cur = std::max(cur, e.second);
        }
        return area;
    }
};

