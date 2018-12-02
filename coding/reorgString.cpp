/*
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

If possible, output any possible result.  If not possible, return the empty string.

Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""

Solution:
http://www.cnblogs.com/grandyang/p/8799483.html
if num of occurence of a char exceed half (n+1)/2 of len, we can not reorg the string
Sort the pair<int, char> (char's occurence) and put into the max heap,
every time, we pick two different chars with top 2 occurence,
append these two chars, and if the remaining occurence > 0, push back to the max heap
continue, until there is either one or zeor char, append this last char
*/
// O(NlogN), 4 ms
class Solution {
public:
    string reorganizeString(string S) {
        map<char, int> table; //<char, occurence>
        for (char c : S) {
            ++table[c];
        }
        // by default, max head according to first key (occurence)
        priority_queue<std::pair<int, char>> queue;
        for (const auto & it : table) {
            if (it.second > (S.size() + 1) / 2) {
                return ""; //more than half the same char, can not do it
            }
            queue.push({it.second, it.first});
        }
        string res;
        while(queue.size() >= 2) {
            // pick the most occured top two chars and append them together
            auto t1 = queue.top(); queue.pop();
            auto t2 = queue.top(); queue.pop();
            res.push_back(t1.second);
            res.push_back(t2.second);
            if (--t1.first > 0) { // still have more
                queue.push(t1);
            }
            if (--t2.first > 0) {
                queue.push(t2);
            }
        }
        if (queue.size() > 0) { // last one
            res.push_back(queue.top().second);
        }
        return res;
    }
};
