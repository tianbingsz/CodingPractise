/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4

Solution: Divide and Conque
findK():
    s = 0, e = n - 1
    while (true):
        pivot position p = parition(s, e)
        A[s, p-1] >= A[p] > A[p+1, e],
        pivot is the p-th order stat
        if p == k - 1 : find k-th largest, return nums[p]
        if p > k - 1: k-th largest is in [s, p-1], e = p-1
        if p < k - 1 : k-th largest is  in [p+1, e], s = p + 1
*/
// O(N) in average, O(N^2) worst case, 56 ms
class Solution {
public:
    int findKthLargest(vector<int>& A, int k) {
        int s = 0, e = A.size() - 1;
        while (true) {
            int p = partition(A, s, e);
            if (p == k - 1) return A[p]; // k-th largest elem, 0-idx
            if (p < k - 1) { // drop A[s, p] < A[k]
                s = p + 1;
            } else {
                e = p - 1; // drop A[p, e] > A[k]
            }
        }
    }

private:
    /*A[s, r-1] >= A[r] > A[r+1, e]*/
    int partition(vector<int> &A, int s, int e) {
        int key = A[s];
        int l = s + 1, r = e;
        while (l <= r) {
            if (A[l] > key) {
                ++l; continue;
            }
            if (A[r] < key) {
                --r; continue;
            }
            // A[l] > key and A[r] < key
            swap(A[l], A[r]);
            ++l; --r;
        }
        swap(A[s], A[r]);
        return r; // A[s, r-1] >= A[r] > A[l,e]
    }
};
