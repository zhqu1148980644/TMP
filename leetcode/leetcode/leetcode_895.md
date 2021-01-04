---
title: Maximum Frequency Stack
date: 2021-01-04
---
Implement FreqStack, a class which simulates the operation of a stack-like data structure.

FreqStack has two functions:

push(int x), which pushes an integer x onto the stack.
pop(), which removes and returns the most frequent element in the stack.
If there is a tie for most frequent element, the element closest to the top of the stack is removed and returned.
 

Example 1:

Input: 
["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
Output: [null,null,null,null,null,null,null,5,7,5,4]
Explanation:
After making six .push operations, the stack is [5,7,5,7,4,5] from bottom to top.  Then:

pop() -> returns 5, as 5 is the most frequent.
The stack becomes [5,7,5,7,4].

pop() -> returns 7, as 5 and 7 is the most frequent, but 7 is closest to the top.
The stack becomes [5,7,5,4].

pop() -> returns 5.
The stack becomes [5,7,4].

pop() -> returns 4.
The stack becomes [5,7].
 

Note:

Calls to FreqStack.push(int x) will be such that 0 <= x <= 10^9.
It is guaranteed that FreqStack.pop() won't be called if the stack has zero elements.
The total number of FreqStack.push calls will not exceed 10000 in a single test case.
The total number of FreqStack.pop calls will not exceed 10000 in a single test case.
The total number of FreqStack.push and FreqStack.pop calls will not exceed 150000 across all test cases.

#### Solutions

1. ##### hash map with stack

- Note that when pop has been called, the maxfreq neither remains the same nor decreases by `1`. Thus maintaining a `maxfreq` variable is sufficient enough, therefore no need to use a treemap/prioeity_queue.
- Borrowed from the official answer.

```cpp
class FreqStack {
public:
    unordered_map<int, int> cnts;
    unordered_map<int, stack<int>> freq;
    int maxfreq = 0;
    FreqStack() {

    }
    
    void push(int x) {
        auto cnt = ++cnts[x];
        maxfreq = max(cnt, maxfreq);
        freq[cnt].push(x);
    }
    
    int pop() {
        if (!freq.size()) return -1;
        auto & items = freq[maxfreq];
        auto x =  items.top(); items.pop();
        if (!items.size())
            freq.erase(maxfreq--);
        if (--cnts[x] == 0) cnts.erase(x);
        

        return x;

    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
```