/*
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.

For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Solution:
find all minutes with n - i bits, all hours with i bits
for h: hours:
    for m : minutes:
        if (h, m valid)
            res.push_back(h + m)
Find n bits to formulate the hour representation is: 0100101...
It is equalivent to pick n 1s, the sum is the n nums from {8, 4, 2, 1}
*/
// beat 100%, backtracking
class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<int> hour{8, 4, 2, 1}; // 1 bit
        vector<int> minute{32, 16, 8, 4, 2, 1}; // 1 bit
        vector<string> res;
        for (int i = 0; i <= num; ++i) {
            auto hours = generate(hour, i);
            auto minutes = generate(minute, num - i);
            for (int h : hours) {
                if (h > 11) continue; // skip
                for (int m : minutes) {
                    if (m > 59) continue; // skip
                    res.push_back(std::to_string(h) + (m < 10 ? ":0" : ":") + std::to_string(m));
                }
            }
        }
        return res;
    }

private:
    // pick n elem (bits) from nums
    vector<int> generate(const vector<int> &nums, int n) {
        vector<int> res;
        helper(nums, 0, n, 0, res);
        return res;
    }

    void helper(const vector<int> &nums, int end, int n, int out, vector<int> &res) {
        if (0 == n) {
            res.push_back(out); return;
        }
        for (int i = end; i < nums.size(); ++i) {
            helper(nums, i + 1, n - 1, out + nums[i], res);
        }
    }
};
