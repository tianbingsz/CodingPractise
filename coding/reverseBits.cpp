/*
Reverse bits of a given 32 bits unsigned integer.

Example:

Input: 43261596
Output: 964176192
Explanation: 43261596 represented in binary as 00000010100101000001111010011100,
             return 964176192 represented in binary as 00111001011110000010100101000000.

Solution:
1. Maintain lo and hi, lo set i-th bit on and hi set 32-i -th bit on
2. Check if n's i-th bit is on, then set res's 32-i -th bit on,
    and continue until we scan all 32 bits of n
*/
// 0 ms, 100%
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t lo = 1;
        uint32_t hi = 1 << 31;
        uint32_t res = 0;
        for (int i = 0; i < 32; ++i) {
            if (n & lo) res |= hi;
            lo <<= 1; hi >>= 1;
        }
        return res;
    }
};
