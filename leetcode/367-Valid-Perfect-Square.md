#### Given a positive integer num, write a function which returns True if num is a perfect square else False.

#### Note: Do not use any built-in library function such as sqrt.

```
Example 1:

Input: 16
Output: true

Example 2:

Input: 14
Output: false
```
#### Solutions

- The problem is equivalent to calculating the square root of the given number.
- See problem 69 for details.

1. ##### newton's method

```c++
class Solution {
public:
    bool isPerfectSquare(int num) {
        long root =  num;
        while (root * root > num) {
            root = (root + num / root) / 2;
        }
        return root * root == num;
    }
};
```

2. ##### binary search

```c++
class Solution {
public:
    bool isPerfectSquare(int num) {
        int lo = 1, hi = num;
        while (lo < hi) {
            long mid = lo + ((hi - lo) >> 1);
            if (mid * mid < num)
                lo = mid + 1;
            else
                hi = mid;
        }
        return (long)lo * lo == num;
    }
};
```