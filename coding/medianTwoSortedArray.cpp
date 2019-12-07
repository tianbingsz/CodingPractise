/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

Solution: Binary Search
findK(A, s1, e1, B, s2, e2, K)
Sorted Array A, [s1, e1], Sorted Array B [s2,e2]
1. find la smallest elem in A, lb smallest in B, s.t. la + lb = K
2. if A[la-1] < B[lb-1]:
        we can drop la smallest elements of A + B, K = K - la
        we can also drop right half of B as these elem > K-th elem in sorted A + B
        findK(A, s1 + la, e1, B, s2, s2 + lb - 1, K - la)
   else:
        we can drop lb smallest elem of A + B, K = K - lb
        we can also drop the right half of A as these elem > K-the elm in sorted A + B
        findK(A, s1, s1 + la - 1, B, s2 + lb, e2, K - lb)
*/
// O(log(M+N)), 32 ms, 97.61%
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        if ((n + m) & 01) {
            return findKSorted(nums1, 0, n - 1, nums2, 0, m - 1, (n + m) / 2 + 1);
        }
        return 0.5 * findKSorted(nums1, 0, n - 1, nums2, 0, m - 1, (n + m) / 2) +
            0.5 * findKSorted(nums1, 0, n - 1, nums2, 0, m - 1, (n + m) / 2 + 1);
    }
private:
    /*find K-th elem in the sorted A and B, assume |A| < |B|, k >= 1*/
    double findKSorted(const vector<int> &A, int s1, int e1,
                      const vector<int> &B, int s2, int e2, int k) {
        if (e1 - s1 > e2 - s2) return findKSorted(B, s2, e2, A, s1, e1, k);
        if (s1 > e1) { // A empty
            return B[k-1];
        }
        if (k == 1) {
            return std::min(A[s1], B[s2]);
        }
        // k >= 2, A, B not empty, find la smallest elem in A, lb smallest in B, la + lb = k
        int la = std::min(k/2, e1 - s1 + 1);
        int lb = k - la;
        if (A[s1 + la - 1] < B[s2 + lb - 1]) {
            // drop left half of A, right half of B, k reduce to k - la
            return findKSorted(A, s1 + la, e1, B, s2, s2 + lb - 1, k - la);
        }
        // drop right half of A, left half of B, k -> k - lb
        return findKSorted(A, s1, s1 + la - 1, B, s2 + lb, e2, k - lb);
    }
};
