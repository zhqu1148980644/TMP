---
title: Jump Game II
date: 2021-01-04
---
### Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

```
Example:

Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

### Note:

You can assume that you can always reach the last index.

### Solutions

1. #### Greedy or breath first search O(n)

- We are initially positioned as the first region, the region we can reach is `num[1:nums[0]]`.
- Loop through the points that is reacheable at the current step, calculate the maximum region that is reacheable in the next step.
- When we get to the maximum region from the last step, update jumps to `jumps + 1`, then back to step 2.

```cpp
#define max(x, y) (x > y ? x : y);
int jump(int* nums, int numsSize){
    int furthest = 0, end = 0, jumps = 0;
    // be caurefull, here the maximum possible i is `last - 1`
    for (int i = 0; i < numsSize - 1; i++) {
        furthest = max(furthest, nums[i] + i);
        if (furthest >= numsSize - 1) {
            jumps++;
            break;
        }
        if (i == end) {
            jumps++;
            end = furthest;
        }
    }
    return jumps;
}
```