/*
On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.

Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

Return the smallest possible value of D.

Example:

Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
Note:

stations.length will be an integer in range [10, 2000].
stations[i] will be an integer in range [0, 10^8].
K will be an integer in range [1, 10^6].
Answers within 10^-6 of the true value will be accepted as correct.

Solution: Binary Search
minmaxGap的最小值left = 0，最大值right = stations[n - 1] - stations[0]。我们每次取mid为left和right的均值，然后计算如果mimaxGap为mid，那么最少需要添加多少个新的stations，记为count。所以如果count > K，说明均值mid选取的过小，使得我们必须新加更多的stations才能满足要求，所以我们就更新left的值；否则说明均值mid选取的过大，使得我们需要小于K个新的stations就可以达到要求，那么我们此时就可以寻找更小的mid，使得count增加到K。如果我们假设stations[N - 1] - stations[0] = m，那么这种实现的空间复杂度是O(1)，时间复杂度是O(nlogm)，可以发现与k无关了。
---------------------
https://blog.csdn.net/magicbean2/article/details/79663323

*/
// O(N log R), R = range of stations
class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        int n = stations.size();
        double lo = 0;
        double hi = stations[n-1] - stations[0];
        while(lo + 1e-6 < hi) {
            double m = (hi + lo)/2.0;
            int ns = numStations(m, stations);
            if (ns > K) { // increase the gap
                lo = m;
            } else { hi = m; }
        }
        return lo;
    }

private:
    int numStations(double gap, const vector<int> &stations) {
        int ns = 0;
        for (int i = 0; i < stations.size() - 1; ++i) {
            // given gap, how many stations needed
            ns += (int) (stations[i+1] - stations[i]) / gap;
        }
        return ns;
    }
};
