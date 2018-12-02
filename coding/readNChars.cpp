/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Example 1:

Input: buf = "abc", n = 4
Output: "abc"
Explanation: The actual number of characters read is 3, which is "abc".
Example 2:

Input: buf = "abcde", n = 5
Output: "abcde"

Solution:
READ (buf, n)
total = 0
while true:
    1. read chars to cache tmp
    char tmp[4]
    len = read(tmp)
    2. copy the remaining chars to buf
    remaining = min (n-total, len)
    copy each char of tmp to buf[total++]
    3. if remaining == 0: implies that finishing reading, break
return total
*/
// Forward declaration of the read4 API.
int read4(char *buf);

// 0 ms, 100%
class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int total = 0;
        while (true) {
            char tmp[4];
            int nChars = read4(tmp);
            int remaining = min(n - total, nChars);
            for (int i = 0; i < remaining; ++i) {
                buf[total++] = tmp[i];
            }
            if (remaining == 0) break;
        }
        return total;
    }
};

/*
Solution:
idx = 0;
while idx < n:
    read either 4 chars or less than 4 chars, l = read(tmp)
    copy tmp to buf if idx < n, otherwise copy unitl n chars
    if l < 4, that implies the remainder after bulk of 4 chars, break
idx is the num of chars read from file into buf
*/
// Forward declaration of the read4 API.
int read4(char *buf);
// 0 ms, 100%
class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int idx = 0;
        char tmp[4];
        while(idx < n) {
            int len = read4(tmp);
            for (int i = 0; i < len && idx < n; ++i) {
                buf[idx++] = tmp[i];
            }
            if (len < 4) break; // remainder chars
        }
        return idx; // # chars read
    }
};
