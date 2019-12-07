/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/*
I have a wish list of cities that I want to visit to, my friends also have city wish lists that they want to visit to. If one of my friends share more than 50% (over his city count in his wish list), he is my buddy.

Given a list of city wish list, output buddy list sorting by similarity.
*/


#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    int similarity;
    string wish;
    Node(const string &n, int sim, const string &w) : name(n), similarity(sim), wish(w) {}
};

class Solution {
public:
    int intersec(const string &s, const string &t) {
        int cnt = 0;
        unordered_set<char> tmp(s.begin(), s.end());
        for (char c : t) {
            if (tmp.count(c)) {
                ++cnt; tmp.erase(c);
            }
        }
        return cnt;
    }

    void addBuddies(const string &myWish, const unordered_map<string,string> &wishList) {
        for (const auto &w : wishList) {
            int sim = intersec(myWish, w.second);
            if (sim >= w.second.size() / 2) {
                cout << "add buddy: " << w.first << " , " << w.second << endl;
                buddies.emplace_back(Node(w.first, sim, w.second));
            }
        }
    }

    string recommendCities(const string &myWish, int k) {
        std:sort(buddies.begin(), buddies.end(),
            [] (const Node &a, const Node &b) {
                return a.similarity > b.similarity;
            });
        string res;
        for (const auto &b: buddies) {
            for (char c : b.wish) {
                if (res.size() == k) return res;
                if (myWish.find(c) != string::npos) continue; // skip
                res += c;
            }
        }
        return res;
    }

private:
    vector<Node> buddies;
};

int main()
{
    cout<<"Hello World" << endl;
    string myWish = "abcd";
    unordered_map<string, string> wishList = {
        {"B1","abef"}, {"B2", "acdg"}, {"B3", "cfeg"}, {"B4", "adxy"}
    };

    Solution sol;
    sol.addBuddies(myWish, wishList);
    string res = sol.recommendCities(myWish, 4);
    cout << "cities: " << res << endl;

    return 0;
}
