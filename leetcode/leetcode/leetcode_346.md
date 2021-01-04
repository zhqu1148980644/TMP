---
title: Moving Average from Data Strea
date: 2021-01-04
---
#### Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

```
Example:

MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
```


#### Solutions

1. ##### queue

```cpp
class MovingAverage {
public:
    int size, cursum = 0;
    queue<int> q;
    /** Initialize your data structure here. */
    MovingAverage(int size) : size(size) {

    }
    
    double next(int val) {
        if (q.size() == size) {
            int out = q.front(); q.pop();
            cursum -= out;
        }
        q.push(val); cursum += val;
        return cursum / (double)q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
```