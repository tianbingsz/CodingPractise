/*
There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum wage expectation.
Return the least amount of money needed to form a paid group satisfying the above conditions.

 

Example 1:

Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately. 

Solution: Heap
Observation: w[j]/q[j] < w[i]/q[i], if we take r = wi/qi, the wage for j, w = r * qj > wj (mini-wage)
So, to satisfy the mini-wage condition, we need to take a larger ratio.
1.One possible optimal solution:
Take the r with the largest ratio, find K workers with smaller ratio and the min sum of qualities.
2.Suppose we visit the workers according their ascending order of ratio, at i-th worker (i > K),
the possible optimal solution is the min sum of qualities for workers in [0, i-1], qSum,
and ratio i, r = wi/qi, that is mCost = min(mCost, qSum * r)
3.So, we need a max heap to maintain the smallest k qaulities to calculate qSum
*/
// O(N logN)
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int n = quality.size();
        vector<pair<double, int>> workers; // ratio, quality
        for (int i = 0; i < n; ++i) {
            workers.push_back({wage[i] * 1.0 / quality[i], quality[i]});
        }
        std:sort(workers.begin(), workers.end(),
                [](const auto &a, const auto &b) {return a.first < b.first;}); // sort by ratio
        priority_queue<int> q; // max heap, store k mini quality
        double qualitySum = 0.0;
        double mCost = 0.0;
        for (int i = 0; i < K; ++i) {
            q.push(workers[i].second);
            qualitySum += workers[i].second;
        }
        // ratio[K] (\sum_i=1^K, qaulity[i])
        mCost = qualitySum * workers[K-1].first;
        for (int i = K; i < n; ++i) {
            q.push(workers[i].second);
            qualitySum += workers[i].second;
            // remove the largest one (> K workers' qaulities)
            qualitySum -= q.top(); q.pop();
            mCost = std::min(mCost, qualitySum * workers[i].first);
        }
        return mCost;
    }
};

/*
For each worker i,
    find other K - 1 workers with acceptable mini-wage and smallest qaulities
*/
// O(N^2 * logN)
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int n = quality.size();
        double mCost = 1e9;
        for (int i = 0; i < n; ++i) {
            double ratio = wage[i] / quality[i];
            vector<double> prices;
            for (int j = 0; j < n; ++i) {
                // not achieve mini wage for j
                if (quality[j] * ratio < wage[j]) continue;
                prices.push_back(quality[j] * ratio);
            }
            if (prices.size() < K) continue; // find less workers
            std::sort(prices.begin(), prices.end());
            double sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += prices[k];
            }
            mCost = std::min(mCost, sum);
        }
        return mCost;
    }
};
