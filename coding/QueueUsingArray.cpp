/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
/*
Assume in your programming language you only have a fixed size array of length 5. Implement a queue datastructure that can get unlimitted number of elements.
Node (with fixedSize - 1 nums) -> (next) Node -> (next) Node ...
Tail : Enqueue
Head : Dequeue
*/

#include <iostream>
#include <vector>
#include <memory>


using namespace std;


class LQueue {
public:
    struct Node {
        vector<int> node;
        shared_ptr<Node> next;
        Node(vector<int> list) : node(list), next(nullptr) {}
    };

    LQueue(int size) : fixedSize(size), size_(0), h(0), t(0) {
        head = tail = make_shared<Node>(vector<int>());
    }

    void enqueue(int num) {
        if (tail == nullptr) {
            cout << "empty Queue" << endl;
        }
        if (t < fixedSize - 1) {
            cout << "enqueue : " << num << endl;
            tail->node.push_back(num);
            cout << "getVal: " << tail->node[t] << endl;
        } else { // add next vector
            cout << "enqueue to newList : " << num << endl;
            tail->next = make_shared<Node>(vector<int>(1, num));
            tail = tail->next;
            t = 0;
        }
        ++t; ++size_;
    }

    int dequeue() {
        if (size_ == 0 || head == nullptr) return -1;
        if (h == fixedSize - 1) {// next vector
            head = head->next;
            if (head == nullptr) return -1;
            h = 0;
        }
        cout << "dequeue: head " << h << endl;
        int val = head->node[h];
        ++h; --size_;
        return val;
    }

private:
    int fixedSize;
    int size_, h, t;
    shared_ptr<Node> head, tail;
};

int main()
{

    auto q = LQueue(4);
    q.enqueue(0);
    q.enqueue(1);
    cout << q.dequeue() << endl;
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;


    return 0;
}
