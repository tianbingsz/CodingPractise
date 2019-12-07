/*
Given an array of prices [p1,p2...,pn] and a target, round each price pi to Roundi(pi) so that the rounded array [Round1(p1),Round2(p2)...,Roundn(pn)] sums to the given target. Each operation Roundi(pi) could be either Floor(pi) or Ceil(pi).

Return the string "-1" if the rounded array is impossible to sum to target. Otherwise, return the smallest rounding error, which is defined as Σ |Roundi(pi) - (pi)| for i from 1 to n, as a string with three places after the decimal.

 

Example 1:

Input: prices = ["0.700","2.800","4.900"], target = 8
Output: "1.000"
Explanation: 
Use Floor, Ceil and Ceil operations to get (0.7 - 0) + (3 - 2.8) + (5 - 4.9) = 0.7 + 0.2 + 0.1 = 1.0 .
Example 2:

Input: prices = ["1.500","2.500","3.500"], target = 10
Output: "-1"
Explanation: 
It is impossible to meet the target.

Solution: Greedy
Key idea: find nFloor, and delta = A[nFloor] - floor(A[nFloor]) 
s.t. for x in diff[0, nFloor) with diff[x] = x - floor(x) < delta, do x = floor(x)
	 for x in diff[nFloor, end) with diff[x] = x - floor(x) > delta, do x = ceil(x)
Then min total_diff = (x - floor(x)) for ix < nFloor 
					+ (ceil(x) -x ) for ix >= nFloor
Here, nth_element(diff.begin(), diff.begin() + nFloor, diff.end()) provides a good solution.
Or, we can sort vector diff, pick the previous nFloor nums with nFloor-th smallest differences,
and pick the remaining nFrac - nFloor nums with ceil(x) - x. 
*/


#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int pivot(vector<double> &nums, int tidx) {
    int key = nums[tidx];
    int s = 0, e = nums.size() - 1;
    swap(nums[s], nums[tidx]);
    ++s;
    while(s <= e) {
        if (nums[s] <= key) {
            ++s; continue;
        }
        if (nums[e] > key) {
            --e; continue;
        }
        swap(nums[s], nums[e]);
        ++s; --e;
    }
    swap(nums[tidx], nums[e]);
    return e; // nums[0..e] <= key < nums[s..end]
}

string mRounds(const vector<string> &nums, int target) {
    int sum = 0;
    int nFrac = 0; 
    vector<double> diff;
    for (int i = 0; i < nums.size(); ++i) {
        double num = stod(nums[i]);
        int fNum = (int) floor(num);
        sum += fNum;
        if (fNum == 1.0 * num) continue;
        ++nFrac;
        diff.push_back(num - fNum);
    }
    if (sum + nFrac < target || sum > target) return "-1";
    int nCeil = target - sum; 
    int nFloor = nFrac - nCeil;
    //sort(diff.begin(), diff.end()); // O(NlogN)
    pivot(diff, nFloor); // O(N)
    string res;
    for (int i = 0; i < diff.size(); ++i) {
        if (i < nFloor) res += to_string(diff[i]) + " ";
        else res += to_string(1.0 - diff[i]) + " ";
    }
    return res;
}

int main()
{
    vector<string> prices = {"0.700","2.800","4.900"};
    string res = mRounds(prices, 8);
    cout << "res: " << res << endl;
    return 0;
}

// 0 ms, 100%
class Solution {
public:
    string minimizeError(vector<string>& prices, int target) {
        int nFrac = 0;
        int sum = 0;
        vector<double> diff;
        for (int i = 0; i < prices.size(); ++i) {
            double num = stod(prices[i]);
            int floorNum = (int)floor(num);
            sum += floorNum;
            if (num == floorNum * 1.0) continue;
            ++nFrac; // non-integer
            diff.push_back(num - floorNum);
        }
        if (nFrac + sum < target || sum > target) return "-1";
        int nCeil = target - sum; // # ceil(x)
        int nFloor = nFrac - nCeil; // # floor(x)
        // for x in diff[0, nFloor), pick floor(x), [nFloor, end), ceil(x)
        std::nth_element(diff.begin(), diff.begin() + nFloor, diff.end());
        double res=0.0;
        for (int i = 0; i < nFrac; ++i) {
            if (i < nFloor) {
                res += diff[i]; // floor(x)
            } else {
                res += 1.0 - diff[i]; // ceil(x)
            }
        }
        string ans = to_string(res);
        return ans.substr(0, ans.find('.') + 4);
    }
};
