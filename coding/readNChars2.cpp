/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.

Example 1:

Given buf = "abc"
read("abc", 1) // returns "a"
read("abc", 2); // returns "bc"
read("abc", 1); // returns ""
Example 2:

Given buf = "abc"
read("abc", 4) // returns "abc"
read("abc", 1); // returns ""

Solution: Cache
Maintain a Cache to store those chars read from file, while not consumed by Reader
READ(buf, n):
    total = 0
    while true:
        1. read file into char tmp[4]
        int len = read4(tmp)
        2. copy tmp to cache
        cache.push_back(tmp[1..len])
        3. read chars from cache
        remaining = min(n - total, len)
        buf[total++] = cache[i = 1 to remaining]
        4. if remaining == 0 // either finishing reading or no chars from file
        break
    return total
*/
// Forward declaration of the read4 API.
int read4(char *buf);

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
            for (int i = 0; i < nChars; ++i) {
                cache.push_back(tmp[i]); // tmp --> cache
            }
            // how many chars remaining to read
            int remaining = min(n - total, (int) cache.size());
            for (int i = 0; i < remaining; ++i) { // cache --> buf
                buf[total++] = cache[i];
            }
            cache.erase(cache.begin(), cache.begin() + remaining);
            if (remaining == 0) break; // finishing read n chars or file exhausted
        }
        return total; // # chars read to buf
    }

private:
    vector<char> cache;
};
