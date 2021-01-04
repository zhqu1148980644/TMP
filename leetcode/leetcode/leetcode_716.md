---
title: Max Stack
date: 2021-01-04
---
Design a max stack that supports push, pop, top, peekMax and popMax.

push(x) -- Push element x onto stack.
pop() -- Remove the element on top of the stack and return it.
top() -- Get the element on the top.
peekMax() -- Retrieve the maximum element in the stack.
popMax() -- Retrieve the maximum element in the stack, and remove it. If you find more than one maximum elements, only remove the top-most one.
Example 1:
MaxStack stack = new MaxStack();
stack.push(5); 
stack.push(1);
stack.push(5);
stack.top(); -> 5
stack.popMax(); -> 5
stack.top(); -> 1
stack.peekMax(); -> 5
stack.pop(); -> 1
stack.top(); -> 5
Note:
-1e7 <= x <= 1e7
Number of operations won't exceed 10000.
The last four operations won't be called when stack is empty.

#### Solutions

- Except for `popMax()`, this problem is the same as `problem 155 Min stack`.

1. ##### two stack worst case O(n) complexity for popMax

- Based on solution in problem 155 with special handling for `popMax`.

```cpp
class MaxStack {
public:
    /** initialize your data structure here. */
    stack<int> s, max;
    MaxStack() {
        max.push(INT_MIN);
    }
    
    void push(int x) {
        if (x >= max.top())
            max.push(x);
        s.push(x);
    }
    
    int pop() {
        if (s.top() == max.top())
            max.pop();
        int res = s.top();
        s.pop();
        return res;
    }
    
    int top() {
        return s.top();
    }
    
    int peekMax() {
        return max.top();
    }
    
    int popMax() {
        // these popped elements can not simply be discard.
        vector<int> popped;
        while (s.top() != max.top()) {
            popped.push_back(s.top()); s.pop();
        }
        int res = max.top();
        s.pop(); max.pop();
        // repush these popped elements and rebuild the max stack
        for (int i = popped.size() - 1; i >= 0; i--)
            push(popped[i]);
        return res;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
```

2. ##### tree map with list O(log(n))

- Use list for mainting the pusing orders and tree map for find the maximum value within the list.
- Note that equivalent keys will be in the order of their insertion order in stl's multimap.

```cpp
class MaxStack {
public:
    /** initialize your data structure here. */
    list<int> s;
    // For tree map doesnot support duplicate keys, use vector<list<int>::iterator> as value type.
    multimap<int, list<int>::iterator> m;

    MaxStack() {
        s.push_back(INT_MIN);
        m.emplace(INT_MIN, s.begin());
    }
    
    void push(int x) {
        s.push_front(x);
        m.emplace(x, s.begin());
    }
    
    int pop() {
        int top = s.front();
        s.pop_front();
        m.erase(prev(m.upper_bound(top)));
        return top;
    }
    
    int top() {
        return s.front();
    }
    
    int peekMax() {
        return m.rbegin()->first;
    }
    
    int popMax() {
        auto maxit = m.rbegin();
        int max = maxit->first;
        s.erase(maxit->second);
        m.erase(--maxit.base());
        return max;
    }
};
```