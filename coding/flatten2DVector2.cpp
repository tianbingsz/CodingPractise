/*
Design and implement an iterator to flatten a 2d vector. It should support the following operations: next and hasNext.



Example:

Vector2D iterator = new Vector2D([[1,2],[3],[4]]);

iterator.next(); // return 1
iterator.next(); // return 2
iterator.next(); // return 3
iterator.hasNext(); // return true
iterator.hasNext(); // return true
iterator.next(); // return 4
iterator.hasNext(); // return false

Solution:
hasNext:
check if the next elem is in a valid row (either current row or the next row)

next:
as hasNext already come to the desired row, just move ++col
*/

#include <iostream>
#include <vector>

using namespace std;

class Vector2D {
public:
    Vector2D(vector<vector<int>> &d) : data(d), row(0), col(0) {}
    
    int next() {
        // pick next elem (r,c), move to next unvisited (r, ++c)
        return data[row][col++];
    }
    
    bool hasNext() {
        if (data.empty()) return false;
        // check row and col for the next elem
        while(row < data.size()) {
            if (col < data[row].size()) return true;
            ++row; col = 0;
        }
        return false;
    }
    
    void remove2() {
        // last elem before (r, c)
        int row2removed = row;
        int col2removed = col;
        if (col == 0) {
            --row2removed;
            col2removed = data[row2removed].size() - 1;
        } else {
            --col2removed;  
        }
        vector<int> list2removed(data[row2removed].begin(), data[row2removed].end());
        list2removed.erase(list2removed.begin() + col2removed);
        data[row2removed].swap(list2removed);
        if (data[row2removed].empty()) {
            data.erase(data.begin() + row2removed);   
            --row;
        }
        // if col == 0, still 0 as we delete last elem of previous row
        if (col > 0) --col; // cur row
        
        cout << "row : " << row << ", col: " << col << endl;
    }
    
    void print() {
        while(hasNext()) {
            cout << "row: " << row << ", " << "col: " << col<< "," << next() << endl;
        }
    }
    
    void printV() {
        for (const auto &v : data) {
            for (int n: v) cout << n << ",";
            cout << endl;
        }
    }

private:
    vector<vector<int>> data;
    int row, col;
    
    
};

int main()
{
   cout << "Hello World" << endl; 
   vector<vector<int>> v = {{1,2}, {3}, {4,5,6}};
   Vector2D sol(v);
   sol.printV();
   cout << "next: " << sol.next() << endl;
   sol.remove2();
   sol.print();
   return 0;
}
