/*
Find Median in Large Integer File of Integers
Find the median from a large file of integers. You can not access the numbers by index, can only access it sequentially. And the numbers cannot fit in memory.
Solution: Binary Search in [left, right]
1. find the guess = (left + right) /2
2. cout how many numvers <= guess and max res in those nums
if cnt == k: return guess as k-th median
if cnt < k: search in [max(res + 1, guess), right]
if cnt > k: search in [left, res]
*/

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

int search(const vector<int> &nums, int k, int left, int right) {
    int res = left;
    int m = (right - left) / 2 + left;
    int cnt = 0;
    for (int n : nums) {
        if (n <= m) {
            ++cnt; res = max(res, n);
        }
    }
    if (k == cnt) return m;
    // in the large num region, median > res
    if (cnt < k) return search(nums, k, max(m, res + 1), right);
    // in the small num region, median < res
    if (cnt > k) return search(nums, k, left, res);
}


double findMedian(const vector<int> &nums) {
    int n = nums.size();
    int minV = INT_MAX, maxV = INT_MIN;
    for (int n : nums) {
        minV = min(minV, n);
        maxV = max(maxV, n);
    }
    if (n & 01) {
        return (double) search(nums, n/2 + 1, minV, maxV);
    }
    return  0.5 * search(nums, n/2, minV, maxV) + 0.5 * search(nums, n/2+1, minV, maxV);
}

int test(const vector<int> &nums) {
    double median = findMedian(nums);
    cout << "\n meidan: " << median << endl;
    return median;
}

bool assertEqual(double res, double expected) {
    double err = abs(res - expected);
    if (err < 1e-5)  {
        cout << "pass " << endl;
    } else {
        cout << "failed " << endl;
    }

}

int main()
{
    cout<<"Hello World";
    vector<int> nums = {-100, 99, 3, 0, 5, 7, 11, 66, -33};
    int expected = 5.0;
    assertEqual(test(nums), expected);

    return 0;
}

