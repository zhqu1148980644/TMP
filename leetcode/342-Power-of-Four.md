#### Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

```
Example 1:

Input: 16
Output: true
Example 2:

Input: 5
Output: false
```

#### Follow up: 
Could you solve it without loops/recursion?

#### Solutions

1. ##### Straight forward

- power of 4 must be power of 2.

```c++
class Solution {
public:
    bool isPowerOfFour(int num) {
        if (num <= 0) return false;
        if (!(num & (num - 1))) {
            while (num >> 2) num >>= 2;
            return num == 1;
        }
        return false;
    }
};
```

or

```c++
class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 
               && !(num & (num - 1)) 
               && num & 0b01010101010101010101010101010101;
    }
};
```

or use 0x55555555(because 0b0101 is 0x5)