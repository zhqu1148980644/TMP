---
title: Wiggle Sort
date: 2021-01-04
---
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

Example:

Input: nums = [3,5,2,1,6,4]
Output: One possible answer is [3,5,1,6,2,4]

#### Solutions


1. ##### reverse pais from the start

- After `pair[i, i + 1]` is correct(suppose increasing), reversing `pair[i + 1, i + 2]`(increasing) would not change the correctness of the previous pair.

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int less = true;
        for (int i = 0; i < (int)nums.size() - 1; i++) {
            if ((nums[i] <= nums[i + 1]) != less)
                swap(nums[i], nums[i + 1]);
            less = !less;
        }
    }
};
```

or use index as the less marker

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 0; i < (int)nums.size() - 1; i++)
            if ((nums[i] <= nums[i + 1]) == (i & 1))
                swap(nums[i], nums[i + 1]);
    }
};

```