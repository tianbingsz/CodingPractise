/*
Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Example 2:

Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.

*/
// 0 ms. 100%
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> sum;
        int carry = 1; // add one first
        for (int i = digits.size() - 1; i >=0; --i) {
            int num = digits[i] + carry;
            if (num >= 10) {
                num %= 10; carry = 1;
            } else carry = 0;
            sum.push_back(num);
        }
        if (carry == 1) {
            sum.push_back(1);
        }
        std::reverse(sum.begin(), sum.end());
        return sum;
    }
};
