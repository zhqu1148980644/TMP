### Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

```
Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

### Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

### Solutions

1. #### dynamic programming O(n)

- Use a dp table to record maximum contiguous sum end in each positions.
- `dp[i] = nums[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0)`

```c++
#define max(x, y) ((x > y) ? x : y)
int maxSubArray(int* nums, int numsSize){
    int m = INT_MIN, last = 0;
    while (numsSize--) {
        last = max(nums[numsSize] + last, nums[numsSize]);
        m = max(m, last);
    }
    return m;
}
```


2. #### divide and conquer