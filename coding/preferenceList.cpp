/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/*
Given a list of everyone's preferred city list, output the city list following the order of everyone's preference order.
For example, input is [[3, 5, 7, 9], [2, 3, 8], [5, 8]]. One of possible output is [2, 3, 5, 8, 7, 9].


*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> topSort(vector<vector<int>> &lists) {
    unordered_map<int, vector<int>> g; // {u , vector}
    unordered_map<int, int> deg; // node->in degree
    unordered_set<int> nums;
    for (auto &l : lists) {
        for (int i = 0; i < l.size() - 1; ++i) {
            g[l[i]].emplace_back(l[i+1]);
            ++deg[l[i+1]];
            nums.insert(l[i]);
        }
        nums.insert(l.back());
    }
    //toplogical sort
    queue<int> q;
    unordered_set<int> visited;
    for (int n : nums) {
        if (deg[n] == 0) {
            q.push(n); visited.insert(n);
        }
    }
    
    vector<int> res;
    while(! q.empty()) {
        int cur = q.front(); q.pop();
        res.emplace_back(cur);
        for (int next : g[cur]) {
            --deg[next];
            if (visited.count(next)) continue;
            if (deg[next] == 0) {
                q.push(next); visited.insert(next);
            }
        }
    }
    return res;
}

int main()
{
    cout<<"Hello World" << endl;
    
    vector<vector<int>> lists = {
        {3, 5, 7, 9}, {2, 3, 8}, {5, 8}
    };
    
    auto res = topSort(lists);
    for (int n : res) {
        cout << n << " ";
    }
    cout << endl;
    /*2 3 5 7 8 9*/
    return 0;
}
