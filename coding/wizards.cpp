/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/*
There are 10 wizards, 0-9, you are given a list that each entry is a list of wizards known by wizard. Define the cost between wizards and wizard as square of different of i and j. To find the min cost between 0 and 9.

For example:

wizard[0] list: 1, 4, 5 

wizard[4] list: 9

wizard 0 to 9 min distance is (0-4)^2+(4-9)^2=41 (wizard[0]->wizard[4]->wizard[9])
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

// Dijkstra's algo
vector<int> shortestPath(vector<vector<int>> &wizards, int s, int t) {
    int n = wizards.size();
    vector<int> parent(n, 0); 
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
    
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, 
        greater<pair<int,int>>> q; // <dist[u], u>
    q.push({0, s});
    while(! q.empty()) {
        auto cur = q.top(); q.pop();
        int curPos = cur.second;
        for (int next : wizards[curPos]) {
            int curDist = cur.first;
            int d = (next - curPos) * (next - curPos);
            if (dist[next] > d + curDist) {
                dist[next] = d + curDist;
                q.push({dist[next], next}); // update
                parent[next] = curPos; // cur -> next
            }  
        }
    }
    vector<int> path;
    int end = t;
    while(end != s) {
        path.push_back(end);
        end = parent[end];
    }
    path.push_back(s);
    std::reverse(path.begin(), path.end());
    return path;
}

int main()
{
    cout<<"Hello World" << endl;
    vector<vector<int>> wizards = {{1, 5, 9}, {2, 3, 9}, {4}, {}, {}, {9}, {}, {}, {}, {}};
    auto path = shortestPath(wizards, 0, 9);
    for (int n : path) {
        cout << n << ", ";
    }
    cout << endl;
   
    /* 0 5 9 */
    return 0;
}
