---
title: Next Permutation
date: 2021-01-04
---
### Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

```
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
```

### Solutions

1. #### reverse point

The rear part of the next smallest point must be monotonous increasing.

- Find the reverse point. i.e. the first number whose next number is larger then itself.
- swap this number with the first(most close) larger one in the rear subtring.
- Reverse the rear substring.

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() <= 1) return;
        int n = nums.size(), i = n - 2;
        // find the first reverse point.
        while (i >= 0 && nums[i] >= nums[i + 1]) i--;
        if (i >= 0) {
            int j = i;
            // find the last element lager than the reverse point.
            while (j + 1 < n && nums[j + 1] > nums[i]) j++;
            swap(nums[i], nums[j]);
        }
        // swap the region to make the next (smallest) permutaion.
        while (i < n - 1)
            swap(nums[++i], nums[--n]);
    }
};
```
