#### Given an integer, write a function to determine if it is a power of three.

```
Example 1:

Input: 27
Output: true
Example 2:

Input: 0
Output: false
Example 3:

Input: 9
Output: true
Example 4:

Input: 45
Output: false
```

#### Follow up:
Could you do it without using any loop / recursion?


#### Solutions

1. ##### log


2. ##### straight forward

```c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n < 1) return false;
        while (n % 3 == 0)
            n /= 3;
        return n == 1;
    }
};
```

3. prime number

- Find the largest number that `x % 3 == 0`  ie. 3 ** 19.
- Divisors of `3 ** 19` are `3 ** 0`, `3 ** 1` .....

```c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};
```