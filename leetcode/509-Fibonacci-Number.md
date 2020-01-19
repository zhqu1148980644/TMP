#### The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

- F(0) = 0,   F(1) = 1
- F(N) = F(N - 1) + F(N - 2), for N > 1.

Given N, calculate F(N).

 

```
Example 1:

Input: 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:

Input: 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:

Input: 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
```

 

#### Note:

0 ≤ N ≤ 30.

#### Solutions

1. ##### iteration

```c++
class Solution {
public:
    int fib(int N) {
        int pprev = 0, prev = 1;
        while (N--) {
            prev += pprev;
            pprev = prev - pprev;
        }
        return pprev;
    }
};
```

2. ##### memoization

```c++
class Solution {
private:
    vector<int> mem;
public:
    int memofib(int N) {
        if (mem[N] != -1)
            return mem[N];
        return memofib(N - 1) + memofib(N - 2);
    }
    int fib(int N) {
        mem = move(vector<int>(N + 1, -1));
        mem[0] = 0;
        if (N > 0) mem[1] = 1;
        return memofib(N);
    }
};
```