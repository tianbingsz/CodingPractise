/*
Given an array w of positive integers, where w[i] describes the weight of index i, write a function pickIndex which randomly picks an index in proportion to its weight.

Note:

1 <= w.length <= 10000
1 <= w[i] <= 10^5
pickIndex will be called at most 10000 times.
Example 1:

Input:
["Solution","pickIndex"]
[[[1]],[]]
Output: [null,0]
Example 2:

Input:
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output: [null,0,1,1,1,0]

Solution:
prob ~ U(0, 1.0)
find the first t, w_t s.t. prob <= \sum_{i=0}^{t} w_i / total
Use binary search to find the index l, s.t. sum[l-1] < prob <= sum[l]
*/
// query O(logN), 100 ms 98.17%
class Solution {
public:
    Solution(vector<int> w) {
        for (int num : w) {
            total += num;
            accW.push_back(total);
        }
    }

    int pickIndex() {
        double prob = rand() / (1.0 * RAND_MAX);
        return binarySearch((int) (prob * total));
    }

private:
    vector<int> accW;
    int total {0};

    /*A[e] <= target < A[s]*/
    int binarySearch(int target) {
        int s = 0, e = accW.size() - 1;
        while(s <= e) {
            int m = s + (e - s) / 2;
            if (accW[m] <= target) {
                s = m + 1;
            } else {
                e = m - 1;
            }
        }
        return s;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(w);
 * int param_1 = obj.pickIndex();
 */


// O(N), 452 ms
class Solution {
public:
    Solution(vector<int> w) {
        weights.assign(w.begin(), w.end());
        for (int n : w) {
            total += n;
        }
    }

    int pickIndex() {
        double prob = rand() / (1.0 * RAND_MAX);
        double sum = 0;
        for (int i = 0; i < weights.size(); ++i) {
            sum += weights[i];
            if (sum > prob * total) return i;
        }
        return -1;
    }
private:
    vector<int> weights;
    int total {0};
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(w);
 * int param_1 = obj.pickIndex();
 */
