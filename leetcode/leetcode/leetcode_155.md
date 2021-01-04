---
title: Min Stack
date: 2021-01-04
---
#### Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
 

```
Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
```

#### Solutions

The difficulty lies in always keeping tack of the current minimum number in the stack.


1. ##### one stack

- Use a single value to store the minimum element of the stack.
- When find a more small value, push the current minimum item into the stack before this new minimum is pushed back.
    - When the minimum element is poped, the second minimum number can be easily fetched from the top of the stack thus the minimum can be correctly recorded.

```cpp
class MinStack {
private:
    stack<int> s;
    int min = INT_MAX;
public:
    /** initialize your data structure here. */
    MinStack() {}

    void push(int x) {
        if (x <= min)  {
            s.push(min);
            min = x;
        }
        s.push(x);
    }

    void pop() {
        int & top = s.top(); s.pop();
        if (top == min) {
            min = s.top();
            s.pop();
        }
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min;
    }
};
```



2. ##### two stack

- Use another stack to keep tack of the minimum numbers.


```cpp
class MinStack {
private:
    stack<int> s;
    stack<int> min;
public:
    /** initialize your data structure here. */
    MinStack() {}

    void push(int x) {
        s.push(x);
        if (min.empty() || x <= min.top()) min.push(x);
    }

    void pop() {
        if (!s.empty()) {
            if (min.top() == s.top()) min.pop();
            s.pop();
        }
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min.top();
    }
};

```