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

- if `n % 4 == 0` then `n  %% 2 == 0`

```c++
bool isPowerOfFour(int num){
    if (num <= 0) return false;
    if (!(num & (num - 1))) {
        while (num >> 2) num = num >> 2;
        if (num == 1) return true;
        else return false;
    }
    else
        return false;
}

```