/*
Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

For example, "great acting skills" and "fine drama talent" are similar, if the similar word pairs are pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is not transitive. For example, if "great" and "fine" are similar, and "fine" and "good" are similar, "great" and "good" are not necessarily similar.

However, similarity is symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

Solution: words1, words2
1. corner case, words1 and words2 should have the same num of strings
2. for pair <x, y>, we insert x+"#"+y and y+"#"+x into set
3. for w1 = words1[i], w2 = words2[i], if we find w1 + "#" + w2 in the set, that implies there is a equvlient pair <w1, w2>
otherwise, no equilevence
*/
// https://leetcode.com/problems/sentence-similarity/description/
// https://leetcode.com/submissions/detail/173599140/
class Solution {
public:
    bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if (words1.empty() && words2.empty()) return true;
        if (words1.empty() || words2.empty()) return false;
        if (words1.size() != words2.size()) return false;
        unordered_set<string> dict;
        for (const auto &pstr : pairs) {
            dict.insert(pstr.first  + "#" + pstr.second);
            dict.insert(pstr.second + "#" + pstr.first);
        }
        for (int i = 0; i < words1.size(); ++i) {
            if (words1[i] == words2[i]) continue; // OK
            if (dict.count(words1[i] + "#" + words2[i]) == 0)
                return false; // no pair exist
        }
        return true;
    }
};
