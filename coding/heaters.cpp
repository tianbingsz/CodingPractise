/*
Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.

Solution:
1.sort houses and heaters
2. for each house position:
    find left and right in hearters to cover the house, s.t. left < house <= right
    get the min dist = min(right - house, left - house)
    update the max radius = max(radius, dist)
*/
// O(NlogN), 69.73%
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int radius = 0;
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());
        for (int house : houses) {
            // first iterator >= house, *(--pos) < house <= *pos
            auto pos = std::lower_bound(heaters.begin(), heaters.end(), house);
            int d1 = (pos == heaters.end()) ? INT_MAX : *pos - house; // left
            int d2 = (pos == heaters.begin()) ? INT_MAX : house - *(--pos); //right
            int r = std::min(d1, d2); // left or right with min dist
            radius = std::max(radius, r);
        }
        return radius;
    }
};

// O(NlogN), binary search, 69.73%
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int radius = 0;
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());
        for (int house : houses) {
            // first iterator >= house, *(--pos) < house <= *pos
            int pos = binarySearch(heaters, house);
            // A[pos - 1] < house <= A[pos]
            int d1 = pos == 0 ? INT_MAX : house - heaters[pos-1]; // left
            int d2 = pos < heaters.size() ? heaters[pos] - house : INT_MAX; // right
            int dist = std::min(d1, d2);
            radius = std::max(dist, radius);
        }
        return radius;
    }
private:
    /*find left and right, s.t. left < target <= right*/
    int binarySearch(const vector<int> &heaters, int target) {
        int l = 0, r = heaters.size() - 1;
        while(l <= r) {
            int m = l + (r - l)/2;
            if (target == heaters[m]) return m;
            if (heaters[m] < target) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return l; // A[r] < target <= A[l]
    }

};

