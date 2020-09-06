Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:  

1 is typically treated as an ugly number.
n does not exceed 1690.



#### Solutions


1. ##### tree set O(nlog(n))


```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        set<long> s; s.insert(1);

        long top;
        for (int i = 1; i <= n; i++) {
            top = *s.begin();
            s.erase(s.begin());
            s.insert(top * 2);
            s.insert(top * 3);
            s.insert(top * 5);
        }

        return top;
    }
};
```


2. ##### dynamic programming

- Similar to merge sort lists.
- Each ugly number can generate 3 different ugly numbers.

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n, 1); dp[0] = 1;
        int i2, i3, i5;
        i2 = i3 = i5 = 0;

        for (int i = 1; i < n; i++) {
            int minval = min(min(dp[i2] * 2, dp[i3] * 3), dp[i5] * 5);
            dp[i] = minval;
            if (dp[i2] * 2 == minval)
                i2++;
            if (dp[i3] * 3 == minval)
                i3++;
            if (dp[i5] * 5 == minval)
                i5++;
        }

        return dp[n - 1];
    }
};
```