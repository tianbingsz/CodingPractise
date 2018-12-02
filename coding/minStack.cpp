/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

Solution:
We use one stack to store the value and one stack to store the current min value.
In each push operation, we push the value x to the stack and an updated min value to the min stack.
When we pop a value from the stack, we also pop the current min value from the min stack.
*/
// O(N), 75.83%
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        if (minSt.empty() || x <= minSt.top()) {
            minSt.push(x);
        }
        st.push(x);
    }

    void pop() {
        if (st.empty()) return;
        if (st.top() == minSt.top()) {
            minSt.pop();
        }
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minSt.top();
    }
private:
    stack<int> st;
    stack<int> minSt;
};

// 98.98%
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        if (st.empty()) minNum = x;
        else minNum = std::min(minNum, x);
        st.push_back(x);
    }

    void pop() {
        if (top() == minNum) {
            if (st.size() > 1) {
                minNum = st[0];
                for (int i = 1; i < st.size() - 1; ++i)
                    minNum = std::min(minNum, st[i]);

            }
        }
        st.pop_back();
    }

    int top() {
        if (!st.empty()) return st.back();
    }

    int getMin() {
        return minNum;
    }
private:
    vector<int> st;
    int minNum {INT_MAX};
};
