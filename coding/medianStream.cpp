/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.


Example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

Solution: Heap
We have two heap,
smallHeap (maxHeap) store the left half of the sorted elems, with top as the largest of this half
largeHeap (minHeap) store the right half of the sorted elems, with top as the smallest of this half
We maitain the relation: smallHeap.size() == largeHeap.size() or smallHeap.size() == 1 + largeHeap.size()
for each num coming:
    add into smallHeap
    move the largest of smallHeap (top) to largeHeap
    if smallHeap.size < largeHeap.size:
        move the smallest of largeHeap (top) to smallHeap
Query:
    if smallHeap.size == largeHeap.size:
        return 0.5 (smallHeap.top + largeHeap.top)
    if smallHeap.size == largeHeap.size + 1:
        return smallHeap.top
*/
// 172 ms, O(NlogN)
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        smallHeap.push(num);
        // move larest elem of small heap to large heap
        largeHeap.push(smallHeap.top());
        smallHeap.pop();
        if (smallHeap.size() < largeHeap.size()) {
            // move the smallest elem of large heap to small heap
            smallHeap.push(largeHeap.top());
            largeHeap.pop();
        }
    }

    double findMedian() {
        return (smallHeap.size() > largeHeap.size()) ? smallHeap.top() :
            0.5 * (smallHeap.top() + largeHeap.top());
    }
private:
    //store the larger half, top is the smallest
    priority_queue<int, vector<int>, std::greater<int>> largeHeap;
    // store smaller half, top is the largest, by default, max heap
    priority_queue<int> smallHeap;
};
// insertion sort, O(N^2), 300 ms
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        insert(num);
    }
    
    double findMedian() {
        if (array.size() % 2 == 1) return array[(array.size() - 1)/2];
        return 0.5 * (array[array.size()/2 - 1] + array[array.size()/2]);
    }
private:
    vector<int> array;
    
    void insert(int num) {
        array.push_back(num); 
        int j = array.size() - 2;
        for (; j >=0;  --j) {
            if (array[j] < num) break;
            if (array[j] >= num) {
                array[j+1] = array[j];
            }    
        }
        array[j+1] = num;
    }
};


