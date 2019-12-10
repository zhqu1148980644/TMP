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
- swap this number with the first larger one in the rear subtring.
- Reverse the rear substring.

```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int r = nums.size(); if (!r) return;
        int rnext;
        // find the first reverse point.
        while (--r) if (nums[r] > nums[r - 1]) break;
        if (rnext = r) {
            // find the last element lager than the reverse point.
            while (rnext + 1 < nums.size() && nums[rnext + 1] > nums[r - 1])
                rnext++;
            swap(nums[r - 1], nums[rnext]);
        }
        rnext = nums.size() - 1;
        while (r < rnext)
            // swap the region to make the next (smallest) permutaion.
            swap(nums[r++], nums[rnext--]);
    }
};
```
