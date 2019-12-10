### Given a 32-bit signed integer, reverse digits of an integer.

#### Example 1:

```
Input: 123
Output: 321
```

### Example 2:

```
Input: -123
Output: -321
```

### Example 3:

```
Input: 120
Output: 21
```

### Note:

Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

### Solutions

1. #### Straight forward.

Watch for edges cases.

```c++
class Solution {
public:
    int reverse(int x) {
        int remain = 0, res = 0;
        int max = INT_MAX / 10;
        int min = INT_MIN / 10;
        while (x != 0) {
            remain = x % 10;
            x /= 10;
            if ((res > max) || (res < min))
                return 0;
            res = res * 10 + remain;
        }
        return res;
    }
};
```
