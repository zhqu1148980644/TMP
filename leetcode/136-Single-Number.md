#### Given a non-empty array of integers, every element appears twice except for one. Find that single one.

#### Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

```
Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4
```

#### Solutions

1. ##### bit operation

- Suppose every numer appeared two times and we iteratively count the number of bit in each position appeared in each number, we will find that the number of bits in each position must be an odd number. i.e `time % 2 == 0`.
- When you `xor` a bit position odd times, this bit position will be set to `0`. ie. `0 ^ 3 ^ 2 ^ 3 ^ 3 = 0`
- What would happen when a number is xored only once ?

```c++
int singleNumber(int* nums, int numsSize){
    int res = 0;
    while(numsSize--) res ^= nums[numsSize];
    return res;
}
```