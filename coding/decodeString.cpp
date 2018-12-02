/*
Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".

Solution:
s = x13[a2[c]]t
string decode(s):
    string res
    res += x
    num = 13
    res += num * decode(a2[c])
    res += decode(t)
return res
*/
// https://leetcode.com/problems/decode-string/description/
// beat 100%
class Solution {
public:
    string decodeString(string s) {
        string res;
        for (int i = 0; i < s.length();) {
            if (!isdigit(s[i])) { // d13[a2[c]]
                res += s[i]; ++i; continue;
            }
            // 13[a2[c]]
            int squreIdx = s.find('[', i);
            int numRepeat = stoi(s.substr(i, squreIdx - i));//13
            int d = dist(s, squreIdx);
            // decode(a2[c]) = acc
            string toRepeat =  decodeString(s.substr(squreIdx+1, d));
            res += repeatString(numRepeat, toRepeat);
            i = squreIdx + d + 2; // [d length str]
        }
        return res;
    }

    string repeatString(int num, const string &s) {
        string res;
        for (int i = 0; i < num; ++i) {
            res += s;
        }
        return res;
    }

    // [a2[c]]
    int dist(const string &s,  int start){
        if (start >= s.length()) return 0;
        int i = 0;
        int numSqure = 0;
        for (; i + start < s.length(); ++i) {
            if (s[i + start] == '[') {
                numSqure ++;
            } else if (s[i+start] == ']') {
                numSqure--;
                // find the first matched ]
                if (numSqure == 0) break;
            }
        }
        return i - 1; // len of a2[c]
    }

};

// a cool version, 0 ms, 100%
    string decodeString(string s) {
        string res;
        for (int i = 0; i < s.length();) {
            if (!isdigit(s[i])) { // d13[a2[c]]
                res += s[i]; ++i; continue;
            }
            // 13[a2[c]]
            int squreIdx = s.find('[', i);
            int numRepeat = stoi(s.substr(i, squreIdx - i));//13
            int d = dist(s, squreIdx);
            // decode(a2[c[de]]) = acc
            string toRepeat =  decodeString(s.substr(squreIdx+1, d));
            res += repeatString(numRepeat, toRepeat);
            i = squreIdx + d + 2; // [d length str]
            if (i < s.length()) {
                res += decodeString(s.substr(i));
                return res;
            }
        }
        return res;
    }

// beat 100%
class Solution {
public:
    string decodeString(string s) {
        stack<string> chars;
        stack<int> nums;
        int num = 0;
        string res; // most inner [[[[res]]]] chars
        for (char c : s) {
            if (isdigit(c)) {
                num = 10 * num + c - '0';
                continue;
            }
            if (isalpha(c)) {
                res += c; continue;
            }
            if (c == '[') {
                // a2[cd]
                nums.push(num); num = 0; // add num
                chars.push(res); res = "";
                continue;
            }
            if (c == ']') {
                // move to end ] of a2[cd], repeat cd 2 times
                string prev = res; // cd
                int nRepeat = nums.top(); nums.pop();
                for (int i = 0; i < nRepeat - 1; ++i) {
                    res += prev;
                }
                res = chars.top() + res; // acdcd
                chars.pop();
            }
        }
        return res;
    }
};
