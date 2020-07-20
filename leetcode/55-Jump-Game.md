### Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

```
Example 1:

Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
```


### Solutions

We say a point is a good point if we can jump to it.

1. #### greedy backward O(n)

- A point can jump to the last good point(the end) if only it can jump to the first good point left the last good point.

```c++
bool canJump(int* nums, int numsSize){
    int cur = numsSize - 1;
    for (int i = numsSize - 2; i >= 0; i--) {
        if (cur - i <= nums[i]) cur = i;
    }
    return !cur;
}
```

2. #### greedy forward O(n)

- May be practically faster than the first version with pre-exit.
- In each step we record the currently reacheable distant point.
    - If the maximum index is smaller than the current index. There is no way to get to the last.
    - Pre-exit when we already can get to the last.

```c++
#define max(x, y) (x > y ? x : y)
bool canJump(int* nums, int numsSize){
    int max_index = 0;
    for (int i = 0; i < numsSize; i++) {
        if (max_index < i) return  false;
        if (max_index >= numsSize - 1) return true;
        max_index = max(i + nums[i], max_index);
    }
    return true;
}
```