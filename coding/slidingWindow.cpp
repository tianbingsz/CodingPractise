/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7]
Explanation:

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Solution: Two Pointers
Maintain a mNum as the max number of A[1..e]
Maintain a window A[s, e], with len = e + 1 - s == k
1. expand: if e + 1 - s < k, move e forward, ++e, update mNum
2. shrink: if e + 1 - s == k, move s forward, ++s,
if A[s] the single max num (mNum), recompute mNum = max(A[s+1, e])
*/
// 40 ms, 99.34%, Two Pointers O(N)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int mNum = INT_MIN;
        int mIdx = -1;
        int s = 0;
        for (int e = 0; e < nums.size(); ++e) {
            if (mNum < nums[e]) { // expand window
                mNum = nums[e]; mIdx = e;
            }
            if (e + 1 - s == k) { // shrink window
                res.push_back(mNum);
                if (s == mIdx) {
                    // will delete A[s], recompute the mNum in A[s+1, e]
                    mNum = INT_MIN;
                    for (int i = s + 1; i <= e; ++i) {
                        if (mNum < nums[i]) {
                            mNum = nums[i]; mIdx = i;
                        }
                    }
                }
                ++s;
            }
        }
        return res;
    }
};

/*
Solution: DeQue
http://www.cnblogs.com/grandyang/p/4656517.html
Use deque to store the num idx in the sliding window
for e = 0 to n-1:
1. shrink
if e - q.front == k, move forward q.pop_front
2. expand
try to push nums[e] into queue in reverse order from front
if nums[q.back()] < nums[e], continuously pop out smaller elem in queue,
thus nums[q.front()] is the max num in window [e - k +1 , e]
3. fetch max num until now (e), res.push_back(nums[q.front()])
*/
// 40 ms, 99.34%
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> q; // used double ended queue to store the idx
        for (int e = 0; e < nums.size(); ++e) {
            // shrink the sliding window
            if (!q.empty() && q.front() + k == e) {
                // exceeding window [q.front, e] > k
                q.pop_front(); // shrink
            }
            // expand the sliding window
            while (!q.empty()  && nums[q.back()] < nums[e]) {
                q.pop_back(); // pop samller num
            }
            q.push_back(e); // push larger num
            // fetch the max num in window till e
            if (e >= k - 1) { // front has the max num so far in window
                res.push_back(nums[q.front()]);
            }
        }
        return res;
    }
};
