/*
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21

*/
// 12 ms, 97.69%
class Solution {
public:
    int reverse(int x) {
        if (x == INT_MIN) return 0;
        if (x < 0) {
            return - reverse(-x);
        }
        long long res = 0;
        while (x > 0) {
            res = 10 * res + x % 10;
            x /= 10;
        }
        if (res > INT_MAX) res = 0; //overflow
        return res;
    }
};
