---
title: Remove Duplicates from Sorted Array II
date: 2021-01-04
---
#### Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

```
Example 1:

Given nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.

It doesn't matter what you leave beyond the returned length.
Example 2:

Given nums = [0,0,1,1,1,1,2,3,3],

Your function should return length = 7, with the first seven elements of nums being modified to 0, 0, 1, 1, 2, 3 and 3 respectively.

It doesn't matter what values are set beyond the returned length.
Clarification:

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by reference, which means modification to the input array will be known to the caller as well.

Internally you can think of this:

// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```


#### Solutions

1. ##### staight forward

- copy the solution codes from problem 26 and relax the limitaion to allow for two consecutive duplicate.

```cpp
int removeDuplicates(int* nums, int numsSize){
    if (numsSize <= 2) return numsSize;
    int i = 1;
    for (int j = 2; j < numsSize; j++) {
        if (nums[j] != nums[i] || nums[j] != nums[i - 1])
            nums[++i] = nums[j];
    }
    return i + 1;
}
```

- Go one step further, the code can be simplified further
- The invariance: for every node `k` before `i`, `array[k] != array[k - 2]`
```cpp

int removeDuplicates(int* nums, int numsSize){
    if (numsSize <= 2) return numsSize;
    int i = 1;
    for (int j = 2; j < numsSize; j++) {
        if (nums[j] != nums[i - 1])
            nums[++i] = nums[j];
    }
    return i + 1;
}
```

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i =  0;
        for (auto & num : nums) {
            if (i < 2 || num != nums[i - 2])
                nums[i++] = num;
        }
        return i;
    }
};
```