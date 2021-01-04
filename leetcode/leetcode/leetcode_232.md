---
title: Implement Queue using Stacks
date: 2021-01-04
---
#### Implement the following operations of a queue using stacks.

- push(x) -- Push element x to the back of queue.
- pop() -- Removes the element from in front of queue.
- peek() -- Get the front element.
- empty() -- Return whether the queue is empty.

```
Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);  
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false
```

#### Notes:

- You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
- Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
- You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).


#### Solutions

1. ##### straight forward

- Use two stack to reverse the popping order.

```cpp
class MyQueue {
private:
    stack<int> input;
    stack<int> output;

public:
    /** Initialize your data structure here. */
    MyQueue() {}

    /** Push element x to the back of queue. */
    void push(int x) {
        input.push(x);
    }

    void check() {
        if (output.empty())
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
    }
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        check();
        auto item = output.top();
        output.pop();
        return item;
    }

    /** Get the front element. */
    int peek() {
        check();
        return output.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return input.empty() && output.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```