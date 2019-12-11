#### Given an integer, write a function to determine if it is a power of two.

```
Example 1:

Input: 1
Output: true
Explanation: 20 = 1
Example 2:

Input: 16
Output: true
Explanation: 24 = 16
Example 3:

Input: 218
Output: false
```

#### Solutions

1. #### bit operation

- `2 ** n` means set the n'th bit to 1.

```c++
bool isPowerOfTwo(int n){
    if (n > 0) return (n && !(n & (n-1)));
    else return false;
}
```