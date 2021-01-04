---
title: Implement Stack using Queues
date: 2021-01-04
---
#### Implement the following operations of a stack using queues.

- push(x) -- Push element x onto stack.
- pop() -- Removes the element on top of the stack.
- top() -- Get the top element.
- empty() -- Return whether the stack is empty.

```
Example:

MyStack stack = new MyStack();

stack.push(1);
stack.push(2);  
stack.top();   // returns 2
stack.pop();   // returns 2
stack.empty(); // returns false
```

#### Notes:

- You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
- Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
- You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).


#### Solutions

1. ##### straight forward

- After pushed a new item, pop every item before this item and push them into the queue.
- push O(n)
- pop/top O(1)

```cpp
class MyStack {
private:
    queue<int> q;

public:
    /** Initialize your data structure here. */
    MyStack() {}

    /** Push element x onto stack. */
    void push(int x) {
        int size = q.size();
        q.push(x);
        while (size--) {
            q.push(q.front());
            q.pop();
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        auto item = q.front();
        q.pop();
        return item;
    }

    /** Get the top element. */
    int top() {
        return q.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```
