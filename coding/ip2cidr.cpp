/*
Given a start IP address ip and a number of ips we need to cover n, return a representation of the range as a list (of smallest possible length) of CIDR blocks.

A CIDR block is a string consisting of an IP, followed by a slash, and then the prefix length. For example: "123.45.67.89/20". That prefix length "20" represents the number of common prefix bits in the specified range.

Example 1:
Input: ip = "255.0.0.7", n = 10
Output: ["255.0.0.7/32","255.0.0.8/29","255.0.0.16/32"]
Explanation:
The initial ip address, when converted to binary, looks like this (spaces added for clarity):
255.0.0.7 -> 11111111 00000000 00000000 00000111
The address "255.0.0.7/32" specifies all addresses with a common prefix of 32 bits to the given address,
ie. just this one address.

The address "255.0.0.8/29" specifies all addresses with a common prefix of 29 bits to the given address:
255.0.0.8 -> 11111111 00000000 00000000 00001000
Addresses with common prefix of 29 bits are:
11111111 00000000 00000000 00001000
11111111 00000000 00000000 00001001
11111111 00000000 00000000 00001010
11111111 00000000 00000000 00001011
11111111 00000000 00000000 00001100
11111111 00000000 00000000 00001101
11111111 00000000 00000000 00001110
11111111 00000000 00000000 00001111

Here X & (-X) = 0000 1000

The address "255.0.0.16/32" specifies all addresses with a common prefix of 32 bits to the given address,
ie. just 11111111 00000000 00000000 00010000.

In total, the answer specifies the range of 10 ips starting with the address 255.0.0.7 .

There were other representations, such as:
["255.0.0.7/32","255.0.0.8/30", "255.0.0.12/30", "255.0.0.16/32"],
but our answer was the shortest possible.

Also note that a representation beginning with say, "255.0.0.7/30" would be incorrect,
because it includes addresses like 255.0.0.4 = 11111111 00000000 00000000 00000100
that are outside the specified range.

Solution: https://www.cnblogs.com/grandyang/p/8440087.html
Example: ip = "255.0.0.7", n = 10
1. step  = 1, as ip = xxxx ... 1111,
n = 10 - 1 = 9
ip = ip + 1 = 255.0.0.8
255.0.0.7/32

2.ip = xxxx... 1000, ==> step = 8 (x & (-x))
n = 9 - 8 = 1
ip = ip + 8 = 255.0.0.16
255.0.0.8/29

3. ip = 255.0.0.16, ==> step = 8
as step > N (1) ==> step = 1
ip = ip + 1 = 255.0.0.17
255.0.0.16/32

X & (-X): e.g. 8 & (-8) = 0000 1000
To expound on the other answer, the two's complement is equal to the one's complement of a number plus 1. Let's look at how adding 1 to the one's complement of 8 goes.

8 -> 00001000 (bin) -> 11110111 (oc) -> 11111000 (tc)
Here, notice how the added 1 moves through the one's complement until it reaches the first 0, flipping that bit and the bits to the right of it. And, also note that the position of the first 0 in the one's complement is also the position of the first 1 in the original binary expression.

In x & (-x), the bits to the left of the first 1 in x will be 0 because they are all still flipped from taking the one's complement. Then, the bits to the right of the first 1 will also be 0 because they were 0 in x (else the first 1 would be earlier).

Thus, the output of x & (-x) will be the power of 2 corresponding to the location of the first 1 in x.
*/

// 4 ms, 78.38%
class Solution {
public:
    vector<string> ipToCIDR(string ip, int n) {
        stringstream s(ip);
        long x = 0;
        string tmp;
        while (getline(s, tmp, '.')) {
            x = x * 256 + stoi(tmp);
        }

        vector<string> res;
        while(n > 0) {
            // lowest bit with 1, e.g. XXX1000
            int step = x & (-x);
            while(step > n) step /= 2;
            res.push_back(convert2binary(x, step));
            x += step;
            n -= step;
        }
        return res;
    }

private:
    string convert2binary(long x, int step) {
        return to_string((x >> 24)&255) + '.' + to_string((x >> 16)&255) + '.'
            + to_string((x >> 8)&255) + '.' + to_string(x & 255)
            + '/' + to_string(32 - (int) log2(step));
    }
};
